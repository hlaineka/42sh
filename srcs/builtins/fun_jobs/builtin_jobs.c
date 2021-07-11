/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 10:21:33 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"

static void	list_active_jobs(int opt, char *jobspec_str, int lst)
{
	t_job	*temp;
	int		i;

	i = 1;
	lst--;
	if (jobspec_str)
	{
		temp = find_pgid_job(g_term, ft_atoi(jobspec_str));
		print_active_job(temp, opt, g_term);
		return ;
	}
	while (i <= lst)
	{
		temp = find_pgid_job(g_term, i);
		i++;
		if (!temp)
			continue ;
		print_active_job(temp, opt, g_term);
	}
}

void	builtin_jobs(void *proc)
{
	t_term		*term;
	t_job		*jobs;
	t_process	*process;
	int			i;
	int			options;

	i = 0;
	options = 0;
	process = proc;
	term = g_term;
	jobs = term->jobs->next;
	if (!jobs->next)
		return ;
	if (process->argc == 1)
	{
		list_active_jobs(options, NULL, get_next_job_pgid(jobs));
		return ;
	}
	i = get_argv_options(process->argv, &options);
	if (options != 0
		&& (options != (1 << L_FLAG))
		&& (options != (1 << P_FLAG)))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "jobs", NULL));
	list_active_jobs(options, process->argv[i], get_next_job_pgid(jobs));
}
