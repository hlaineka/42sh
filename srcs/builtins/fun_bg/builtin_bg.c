/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 23:41:34 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "job_control.h"

static void	change_job_to_current(t_job *job, t_term *term)
{
	t_job		*prev;

	prev = term->jobs;
	while (prev->next != job && prev->next != NULL)
		prev = prev->next;
	prev->next = job->next;
	job->next = term->jobs->next;
	term->jobs->next = job;
}

void	builtin_bg(void *proc)
{
	t_term		*term;
	t_process	*process;
	t_job		*job;

	process = proc;
	term = g_term;
	if (process->argc == 1)
		job = get_current_job_builtin(term);
	else
		job = find_pgid_job(term, ft_atoi(process->argv[1]));
	if (!job)
	{
		process->status = 1;
		return ((void)err_builtin(E_NO_SUCH_JOB, "bg", process->argv[1]));
	}
	job->bg = 1;
	job->notified = 0;
	print_active_job(job, ((1 << B_FLAG) | (1 << J_FLAG)), term);
	start_stopped_job(job, term);
	change_job_to_current(job, term);
	tcsetpgrp(term->fd_stderr, getpgrp());
}
