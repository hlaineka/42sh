/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_stopped_job.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/06 17:09:59 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int	start_stopped_job(t_job *job, t_term *term)
{
	t_process	*proc;

	proc = job->first_process;
	kill(-(job->first_process->pid), SIGCONT);
//	if (!job->bg)	// here or after first SIGCONT signal?
	tcsetpgrp(term->fd_stderr, job->first_process->pid);
/*
	while (proc)
	{
		if (proc->stopped)
			kill(proc->pid, SIGCONT);
		proc = proc->next;
	}
*/
	return (0);		// todo: make this return void or error check -1?
}
