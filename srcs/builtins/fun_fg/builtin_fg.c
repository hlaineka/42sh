/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/10 12:17:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "job_control.h"

void	builtin_fg(void *proc)
{
	t_term		*term;
	t_process	*process;
	t_job		*job;

	process = proc;
	term = g_term;
	if (process->argc == 1)
		job = find_last_stopped_job(term);
	else
		job = find_pgid_job(term, ft_atoi(process->argv[1]));
	if (!job)
	{
		process->status = 1;
		return ((void)err_builtin(E_NO_SUCH_JOB, "fg", process->argv[1]));
	}
	job->bg = 0;
	start_stopped_job(job, term);
	wait_job_and_get_status(job, term);
	tcsetpgrp(term->fd_stderr, getpgrp());
}
