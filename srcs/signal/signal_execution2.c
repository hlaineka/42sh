/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_execution2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:37:48 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/12 10:38:21 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	kill_processes_before_pid(t_job *job, pid_t pid)
{
	t_process	*proc;

	proc = job->first_process;
	while (proc)
	{
		if (!proc->completed && (proc->pid != pid))
			kill(proc->pid, SIGKILL);
		proc = proc->next;
	}
}
