/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_to_get_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:51:45 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/09 21:35:44 by hhuhtane         ###   ########.fr       */
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

static void	recursive_wait(t_process *proc, t_term *term)
{
	if (proc->next)
		recursive_wait(proc->next, term);
	if (!proc->completed || !proc->stopped)
	{
		wait_to_get_status(proc);
		term->last_return = proc->status;
	}
	ft_printf("proc_id %d\n", proc->pid);
}

void	wait_job_and_get_status(t_job *job, t_term *term)
{
	t_process	*proc;

	(void)term;
	signal(SIGCHLD, SIG_DFL);
//	set_signal_execution();
	proc = job->first_process;
	recursive_wait(proc, term);
/*
	while (proc)
	{
		if (!proc->completed && !proc->stopped)
		{
			ft_printf("proc_id %d\n", proc->pid);
			wait_to_get_status(proc);
			term->last_return = proc->status;
		}
		proc = proc->next;
	}
*/
}
