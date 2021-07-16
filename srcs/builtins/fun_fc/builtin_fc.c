/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/16 10:29:21 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"
#include "history.h"

/*
static int	open_temp_file(void)
{
	int			fd;

	fd = open("/tmp/.42sh_oldies_temp", O_RDWR | O_CREAT);

}
*/

static void	fc_el(t_term *term, int options)
{
	int			last;
	int			i;
	char		**history;
	

	last = get_last_history_index(term->history);
	history = term->history;
	last--;
	if (last > 15)
		i = last - 15;
	else
		i = 1;
	while (i <= last)
	{
		if (options & (1 << N_FLAG))
			ft_printf("\t%s\n", history[i]);
		else
			ft_printf("%d\t%s\n", i, history[i]);
		i++;
	}
}

void	builtin_fc(void *proc)
{
	t_term		*term;
	t_job		*jobs;
	t_process	*process;
	int			i;
	int			options;

//	int			argc;
//	char		**argv;
//	char		**history;

	i = 0;
	options = 0;
	process = proc;
	term = g_term;
	jobs = term->jobs->next;
	i = get_argv_options(process->argv, &options);
	if (options & ~((1 << E_FLAG) | (1 << L_FLAG) | (1 << N_FLAG)
		| (1 << R_FLAG) | (1 << S_FLAG)))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "fc", NULL));
	ft_printf("fc options correct\n");
	if (options & (1 << L_FLAG))
		fc_el(term, options);
}
