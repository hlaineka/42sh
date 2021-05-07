/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:07:56 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/07 14:39:54 by hhuhtane         ###   ########.fr       */
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

	ft_printf("BOBO");
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

void	sig_tstp_handler(void)
{
	t_job		*jobs;
	t_process	*proc;

	jobs = g_term->jobs;
	while (jobs)
	{
		proc = jobs->first_process;
		while (proc)
		{
			kill(proc->pid, SIGTSTP);
			proc->stopped = 1;
			proc = proc->next;
		}
	}
}

void	sig_handler_exec(int signo)
{
	t_job		*jobs;
	t_process	*proc;

	ft_printf("signo:%d", signo);
	if (signo == SIGCHLD)
		sig_child_handler();
	if (signo == SIGTSTP)
		sig_tstp_handler();
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
		ft_putchar('\n');
	}
}

void	set_signal_execution(void)
{
	if ((signal(SIGINT, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGCONT, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGINT, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGTSTP, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGTERM, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGQUIT, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGHUP, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGPIPE, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGALRM, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGXCPU, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGXFSZ, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGABRT, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGVTALRM, sig_handler_exec) == SIG_ERR)
		|| (signal(SIGPROF, sig_handler_exec) == SIG_ERR))
		ft_exit(0);
}
