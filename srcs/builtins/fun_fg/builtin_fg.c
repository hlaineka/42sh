/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/10 21:13:05 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "job_control.h"

static void	change_job_to_current(t_job *job, t_term *term)
{
	t_job		*prev;

	prev = term->jobs;
	while(prev->next != job && prev->next != NULL)
		prev = prev->next;
	prev->next = job->next;
	job->next = term->jobs->next;
	term->jobs->next = job;
}

void	builtin_fg(void *proc)
{
	t_term		*term;
	t_process	*process;
	t_job		*job;

	process = proc;
	term = g_term;
	if (process->argc == 1)
		job = get_current_job_builtin(term);
//		job = find_last_stopped_job(term);
	else
		job = find_pgid_job(term, ft_atoi(process->argv[1]));
	if (!job)
	{
		process->status = 1;
		return ((void)err_builtin(E_NO_SUCH_JOB, "fg", process->argv[1]));
	}
	job->bg = 0;
	ft_printf("change to just job->command %s\n", job->command);
	start_stopped_job(job, term);
	wait_job_and_get_status(job, term);
	change_job_to_current(job, term);
	tcsetpgrp(term->fd_stderr, getpgrp());
}
