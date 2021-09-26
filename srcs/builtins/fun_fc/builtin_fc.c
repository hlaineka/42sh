/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/26 20:46:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"
#include "history.h"

static int	get_first_and_last(t_process *proc, t_term *term, t_fc *fc)
{
	fc->first = fc_get_command_index(fc, term, proc);
	fc->last = fc_get_command_index(fc, term, proc);
	if (fc->first < 0 || fc->last < 0)
		return (-1);
	if (fc->options & (1 << S_FLAG) && fc->first == 0)
		fc->first = fc->last;
	return (0);
}

static t_fc	get_fc_options(t_process *proc, t_term *term)
{
	t_fc		fc;
	int			temp;

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

static int	fc_rest(t_term *term, t_fc *fc)
{
	t_process	*temp_proc;
	int			ret;

	ret = 0;
	if (fc->first == 0)
		fc->first = get_last_history_index(term->history) - 1;
	temp_proc = init_process(term);
	temp_proc->argv[0] = "env";
	if (fc->editor[0] == '\0')
		temp_proc->argv[1] = "vim";
	else
		temp_proc->argv[1] = fc->editor;
	ret = hist_to_file(fc, term->history, term, temp_proc);
	free(temp_proc->argv);
	ft_free(temp_proc);
	return (ret);
}

void	builtin_fc(void *proc)
{
	t_term		*term;
	t_process	*process;
	char		**history;
	int			options;
	t_fc		fc;

	signals_to_default();
	process = proc;
	term = g_term;
	history = term->history;
	fc = get_fc_options(process, term);
	options = fc.options;
	if (options & ~((1 << E_FLAG) | (1 << L_FLAG) | (1 << N_FLAG)
			| (1 << R_FLAG) | (1 << S_FLAG)))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "fc", NULL));
	if (!(fc.options & (1 << L_FLAG)))
		ft_memdel((void **)(&history[get_last_history_index(history) - 1]));
	if (get_first_and_last(proc, term, &fc) == -1)
		return ;
	if (options & (1 << L_FLAG))
		fc_el(term, &fc, fc.options);
	else if (options & (1 << S_FLAG))
		fc_es(term, &fc, fc.options);
	else
		process->status = fc_rest(term, &fc);
}
