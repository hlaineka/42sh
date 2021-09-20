/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_stopped_job.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 18:29:38 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int	start_stopped_job(t_job *job, t_term *term)
{
	t_process	*proc;

	if (!job || !job->first_process)
		return (0);
	proc = job->first_process;
	kill(-(job->pgid), SIGCONT);
	if (!job->bg)
		tcsetpgrp(term->fd_stderr, job->pgid);
	while (proc)
	{
		if (proc->stopped)
			proc->stopped = 0;
		proc = proc->next;
	}
	return (0);
}
