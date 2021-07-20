/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/20 20:13:47 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"
#include "history.h"

static int	open_temp_file_write(void)
{
	int			fd;

	fd = open("/Users/hhuhtane/.42sh_oldies_temp", O_WRONLY | O_CREAT | O_TRUNC);
	return (fd);
}

static int	open_temp_file_read(void)
{
	int			fd;

	fd = open("/Users/hhuhtane/.42sh_oldies_temp", O_RDONLY);
	return (fd);
}

static int	write_history_to_file(t_fc *fc, char **hist, t_term *term, t_process *proc)
{
	int		i;
	int		fd;
	char	*line;
	int		ret;

	fd = open_temp_file_write();
	if (fc->first)
		i = fc->first;
	else
		i = get_last_history_index(hist) - 1;
	while (i <= fc->last)
		ft_printf_fd(fd, "%s\n", hist[i++]);
	close(fd);
	builtin_env(proc);
	fd = open_temp_file_read();
	ret = get_next_line(fd, &line);
//	ft_printf("line=%s ret=%d\n", line, ret);
	while (ret > 0)
	{
		parse_and_execute(line, term);
		ret = get_next_line(fd, &line);
//		ft_printf("line=%s ret=%d\n", line, ret);
	}
	close(fd);
//	parse_and_execute(line, term);
	return (1);
}

static int	get_command_index_with_arg(t_fc *fc, t_term *term, t_process *pr)
{
	int		temp;
	int		i;

	i = get_last_history_index(term->history);
	if (!pr->argv[fc->i])
		return (0);
	temp = ft_atoi(pr->argv[fc->i]);
	if (temp >= i)
		return (-1);
	if (temp == 0)
	{
		while (i-- > 0)
		{
//			ft_printf("i=%d\n", i);
			if (ft_strnstr(term->history[i], pr->argv[fc->i],
				ft_strlen(pr->argv[fc->i])))
			{
				temp = i;
				break ;
			}
			i--;
		}
	}
	else if (temp < 0)
		temp = get_last_history_index(term->history) - temp - 1;
	fc->i++;
	return (temp);
}

static int	get_first_and_last(t_process *proc, t_term *term, t_fc *fc)
{
	fc->first = get_command_index_with_arg(fc, term, proc);
//	ft_printf("first=%d\n", fc->first);
	fc->last = get_command_index_with_arg(fc, term, proc);
//	ft_printf("last=%d\n", fc->last);
	if (fc->first < 0 || fc->last < 0)
		return (-1); //todo error message
	if (fc->last == 0)
		fc->last = get_last_history_index(term->history) - 1;
	if (fc->options & (1 << S_FLAG) && fc->first == 0)
		fc->first = fc->last;
	if (fc->first == 0)
	{
		if (fc->last > 15)
			fc->first = fc->last - 15;
		else
			fc->first = 1;
		return (0);
	}

//	ft_printf("first=%d last=%d\n", fc->first, fc->last);
	return (0);
}

static t_fc	get_fc_options(t_process *proc, t_term *term)
{
	t_fc	fc;
	int		temp;

	(void)term;
	temp = 0;
	ft_bzero(&fc, sizeof(t_fc));
	fc.i = get_argv_options(proc->argv, &temp);
	if (temp & (1 << E_FLAG) && proc->argv[fc.i])
		ft_strcpy(fc.editor, proc->argv[fc.i++]);
	while (temp)
	{
		fc.options = fc.options | temp;
		temp = 0;
		fc.i += get_argv_options_next(proc->argv + fc.i, &temp);
		if (temp & (1 << E_FLAG) && proc->argv[fc.i])
			ft_strcpy(fc.editor, proc->argv[fc.i++]);
	}
	fc.options = fc.options | temp;
	return (fc);
}

static void	fc_el(t_term *term, t_fc *fc, int options)
{
	int			last;
	int			i;
	int			temp_i;
	char		**history;
	
	if (fc->last)
		last = fc->last;
	else
		last = get_last_history_index(term->history) - 1;
	history = term->history;
	if (fc->first)
		i = fc->first;
	else if (last > 15)
		i = last - 15;
	else
		i = 1;
	while (i <= last)
	{
		if (options & (1 << R_FLAG))
			temp_i = last;
		else
			temp_i = i;
		if (options & (1 << N_FLAG))
			ft_printf("\t%s\n", history[temp_i]);
		else
			ft_printf("%d\t%s\n", temp_i, history[temp_i]);
		if (options & (1 << R_FLAG))
			last--;
		else
			i++;
	}
}

void	builtin_fc(void *proc)
{
	t_term		*term;
	t_job		*jobs;
	t_process	*process;
	int			options;
	t_fc		fc;
	t_process	*temp_proc;

	signals_to_default();
	process = proc;
	term = g_term;
	jobs = term->jobs->next;
	fc = get_fc_options(process, term);
	options = fc.options;
	if (options & ~((1 << E_FLAG) | (1 << L_FLAG) | (1 << N_FLAG)
		| (1 << R_FLAG) | (1 << S_FLAG)))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "fc", NULL));
//	ft_printf("fc options correct. fc.i=%d\n", fc.i);
	if (!(fc.options & (1 << L_FLAG)))
		ft_memdel((void**)(&term->history[get_last_history_index(term->history) - 1]));
//	ft_printf("before get_first_and_last\n");
	get_first_and_last(proc, term, &fc);
//	ft_printf("editor=%s first=%d last=%d\n", fc.editor, fc.first, fc.last);
	if (options & (1 << L_FLAG))
		fc_el(term, &fc, fc.options);
	else if (options & (1 << S_FLAG))
	{
		ft_putendl("S_FLAG");
		fc_es(term, &fc, fc.options);
		return ;
	}
	else
	{
		temp_proc = init_process(term);
		temp_proc->argv[0] = "env";
		if (fc.editor[0] == '\0')
			temp_proc->argv[1] = "vim";
		else
			temp_proc->argv[1] = fc.editor;
		temp_proc->argv[2] = "/Users/hhuhtane/.42sh_oldies_temp";
		write_history_to_file(&fc, term->history, term, temp_proc);
		ft_free(temp_proc);
		free(temp_proc->argv);
	}
}
