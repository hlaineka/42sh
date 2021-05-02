/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:07:56 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 12:22:47 by hlaineka         ###   ########.fr       */
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

void	handle_process(t_process *proc, int status)
{
	proc->status = status;
	if (WIFEXITED(status))
	{
		proc->completed = 1;
		proc->status = WEXITSTATUS(status);
	}
	else if (WIFSTOPPED(status))
	{
		proc->stopped = 1;
		proc->status = WIFSTOPPED(status);
	}
	else if (WIFSIGNALED(status))
	{
		proc->completed = 1;
		proc->status = WTERMSIG(status);
	}
}

void	sig_child_handler(void)
{
	pid_t		pid;
	int			status;
	t_job		*jobs;
	t_process	*proc;

	pid = waitpid(-1, &status, WNOHANG);
	jobs = g_term->jobs;
	while (jobs)
	{
		proc = jobs->first_process;
		while (proc)
		{
			if (pid == proc->pid)
			{
				handle_process(proc, status);
				kill_processes_before_pid(jobs, pid);
				return ;
			}
			proc = proc->next;
		}
		jobs = jobs->next;
	}
}

void	sig_handler_exec(int signo)
{
	t_job		*jobs;
	t_process	*proc;

	if (signo == SIGCHLD)
		sig_child_handler();
	if (signo == SIGINT)
	{
		jobs = g_term->jobs;
		while (jobs)
		{
			proc = jobs->first_process;
			while (proc)
			{
				kill(proc->pid, SIGINT);
				proc = proc->next;
			}
			jobs = jobs->next;
		}
	}
}
