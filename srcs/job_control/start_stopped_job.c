/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_stopped_job.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/10 13:02:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

/*
static void	change_job_to_current(t_job *job, t_term *term)
{
	t_job		*temp;

	temp = term->jobs;
	while(temp->next != job || temp->next != NULL)
		temp = temp->next;
	temp->next = job->next;
	job->next = term->jobs->next;
	term->jobs->next = job;
}
*/

int	start_stopped_job(t_job *job, t_term *term)
{
	t_process	*proc;

	if (!job || !job->first_process)
		return (0);
	proc = job->first_process;
	kill(-(job->first_process->pid), SIGCONT);
//	if (!job->bg)	// here or after first SIGCONT signal?
	tcsetpgrp(term->fd_stderr, job->pgid);
	while (proc)
	{
		if (proc->stopped)
			proc->stopped = 0;
//			kill(proc->pid, SIGCONT);
		proc = proc->next;
	}
	return (0);		// todo: make this return void or error check -1?
}
