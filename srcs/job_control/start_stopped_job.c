/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_stopped_job.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/04 19:12:02 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int	start_stopped_job(t_job *job, int fg)
{
	t_process	*proc;

	proc = job->first_process;
//	if (fg)
//		
	while (proc)
	{
		if (proc->stopped)
			kill(proc->pid, SIGCONT);
		proc = proc->next;
	}
	return (0);		// todo: make this return void or error check -1?
}
