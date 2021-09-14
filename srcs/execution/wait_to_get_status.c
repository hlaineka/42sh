/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_to_get_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:51:45 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 19:34:50 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_signal.h"

void	wait_to_get_status(t_process *proc, int bg)
{
	int		status;
	pid_t	wpid;

	status = 0;
	if (bg)
	{
		return ;
	}
	wpid = waitpid(proc->pid, &status, WUNTRACED);
	if (wpid == -1)
		exit(EXIT_FAILURE);
	while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
	{
		wpid = waitpid(proc->pid, &status, WUNTRACED);
		if (wpid == -1)
			exit(EXIT_FAILURE);
	}
	get_status_and_condition(proc, status);
}

static void	recursive_wait(t_process *proc, t_job *job, t_term *term)
{
	if (proc->next)
		recursive_wait(proc->next, job, term);
	if (!proc->completed && !proc->stopped)
	{
		wait_to_get_status(proc, job->bg);
		term->last_return = proc->status;
	}
}

void	wait_job_and_get_status(t_job *job, t_term *term)
{
	t_process	*proc;

	set_signal_execution();
	proc = job->first_process;
	recursive_wait(proc, job, term);
}
