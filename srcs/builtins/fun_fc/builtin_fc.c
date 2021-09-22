/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/22 22:26:43 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"
#include "history.h"

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
		if (pr->argv[fc->i][0] == '-' && pr->argv[fc->i][1] == '-')
			return (0);
		while (i-- > 0)
		{
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
	fc->last = get_command_index_with_arg(fc, term, proc);
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

void	builtin_fc(void *proc)
{
	t_term		*term;
	t_process	*process;
	int			options;
	t_fc		fc;
	t_process	*temp_proc;

	signals_to_default();
	process = proc;
	term = g_term;
	fc = get_fc_options(process, term);
	options = fc.options;
	if (options & ~((1 << E_FLAG) | (1 << L_FLAG) | (1 << N_FLAG)
		| (1 << R_FLAG) | (1 << S_FLAG)))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "fc", NULL));
	if (!(fc.options & (1 << L_FLAG)))
		ft_memdel((void**)(&term->history[get_last_history_index(term->history) - 1]));
	get_first_and_last(proc, term, &fc);
	if (options & (1 << L_FLAG))
		fc_el(term, &fc, fc.options);
	else if (options & (1 << S_FLAG))
	{
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
//		temp_proc->argv[2] = "/Users/hhuhtane/.42sh_oldies_temp";
		hist_to_file(&fc, term->history, term, temp_proc);
//		write_history_to_file(&fc, term->history, term, temp_proc);
		ft_free(temp_proc);
		free(temp_proc->argv);
	}
}
