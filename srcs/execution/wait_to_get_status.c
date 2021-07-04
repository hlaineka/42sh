/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_to_get_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:51:45 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/04 21:37:56 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_signal.h"

void	wait_to_get_status(t_process *proc)
{
	int		status;
	pid_t	wpid;

	status = 0;
	wpid = waitpid(proc->pid, &status, WUNTRACED);
	if (wpid == -1)
		exit(EXIT_FAILURE);		//todo error message
	while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
	{
		wpid = waitpid(proc->pid, &status, WUNTRACED);
		if (wpid == -1)
			exit(EXIT_FAILURE);	//todo error message
	}
	get_status_and_condition(proc, status);
}

void	wait_job_and_get_status(t_job *job, t_term *term)
{
	t_process	*proc;

	(void)term;
	signal(SIGCHLD, SIG_DFL);
//	set_signal_execution();
	proc = job->first_process;
	while (proc)
	{
		if (proc->completed || proc->stopped)
		{
			wait_to_get_status(proc);
		}
		proc = proc->next;
	}
}
