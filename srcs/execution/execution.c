/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:28:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/23 11:01:45 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"


void	set_read(int* lpipe)
{
	dup2(lpipe[0], STDIN_FILENO);
	close(lpipe[0]); // we have a copy already, so close it
	close(lpipe[1]); // not using this end
}

void	set_write(int* rpipe)
{
	dup2(rpipe[1], STDOUT_FILENO);
	close(rpipe[0]); // not using this end
	close(rpipe[1]); // we have a copy already, so close it
}

void	fork_and_chain_pipes2(int *lpipe, int *rpipe, t_process *current)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		current->pid = pid;
		return ;
	}
	if (lpipe)
		set_read(lpipe);
	if (rpipe)
		set_write(rpipe);
	if (!is_builtin(current))
	{
		current->status = exec_tprocess(current);
//		ft_printf_fd(4, "after EXEC_PROCESS %s status=%d\n", current->argv[0], current->status);
	}
	exit(current->status);
}

// start_new_jobs duplicates fds according to jobs structure.
// should it return int value to indicate if there was an error?

void	start_new_jobs(t_job *jobs, int *rpipe)
{
	t_process	*current;

//	close(STDIN_FILENO);
//	close(STDOUT_FILENO);
//	close(STDERR_FILENO);
	dup2(jobs->fd_stdin, STDIN_FILENO);
	dup2(jobs->fd_stderr, STDERR_FILENO);
	close(jobs->fd_stdin);
	close(jobs->fd_stderr);
	current = jobs->first_process;
// If jobs have more than one processes
	if (current->next)
	{
		pipe(rpipe);
		dup2(rpipe[1], STDOUT_FILENO);
		close(rpipe[1]);
//		lpipe[0] = rpipe[0];
	}
	else
		dup2(jobs->fd_stdout, STDOUT_FILENO);
}

void	set_pipeline_to_process(t_process *cur, t_job *jobs, int *rpipe)
{
	if (cur && cur->next)
	{
		dup2(rpipe[0], STDIN_FILENO);
		close(rpipe[0]);
		pipe(rpipe);
		dup2(rpipe[1], STDOUT_FILENO);
		close(rpipe[1]);
	}
	else if (cur)
	{
		dup2(rpipe[0], STDIN_FILENO);
		close(rpipe[0]);
		dup2(jobs->fd_stdout, STDOUT_FILENO);
	}
}

/*
static void	redirect_process(int fd_in, int fd_out, int fd_err)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (fd_err != STDERR_FILENO)
	{
		dup2(fd_err, STDERR_FILENO);
		close(fd_err);
	}
}
*/

void	wait_children(t_job *job)
{
	t_process	*proc;
	int			status;

	proc = job->first_process;
	while (proc->next)
	{
		if (proc->status || proc->completed)
			return ;

//		if (proc->completed || proc->stopped)
//		{
//			ft_putendl_fd(proc->argv[0], 4);
			proc = proc->next;
//		}
	}
//	ft_putchar_fd('\n', 4);
//	ft_putendl_fd("123\n", 4);
	waitpid(proc->pid, &status, 0);
//	ft_putendl_fd("123\n", 4);
	proc->status = status;
}

void	execute_job(t_job *jobs, t_term *term);
// void	execute_pipeline(t_job *job, t_term *term)
void	execute_jobs(t_job *jobs, t_term *term)
{
	t_job		*job;
	t_process	*current;
	int			lpipe[2];
	int			rpipe[2];

	job = jobs;
	current = job->first_process;
	if (!current->next)
	{
		execute_job(jobs, term);
		return ;
	}
	current->envp = term->envp;
	current->argc = ft_strarrlen(current->argv);
	pipe(rpipe);
	fork_and_chain_pipes2(NULL, rpipe, current);
	lpipe[0] = rpipe[0];
	lpipe[1] = rpipe[1];
	current = current->next;
	while (current->next)
	{
		current->envp = term->envp;
		current->argc = ft_strarrlen(current->argv);
		pipe(rpipe);
		fork_and_chain_pipes2(lpipe, rpipe, current);
		close(lpipe[0]);
		close(lpipe[1]);
		lpipe[0] = rpipe[0];
		lpipe[1] = rpipe[1];
		current = current->next;
	}
	current->envp = term->envp;
	current->argc = ft_strarrlen(current->argv);
	dup2(term->fd_stdout, STDOUT_FILENO);
	fork_and_chain_pipes2(lpipe, NULL, current);
	close(lpipe[0]);
	close(lpipe[1]);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
//	ft_putendl("EXITEXITEXIT");
	wait_children(job);
}

// this executes a job not jobs

void	execute_job(t_job *jobs, t_term *term)
{
	t_process	*current;
	pid_t		pid;
//	int			rpipe[2];

	current = jobs->first_process;

/*	if (current->next)
	{
		execute_pipeline(jobs, term);
		return ;
	}
*/
	ft_printf_fd(4, "EXECUTE_JOBS\n");
//	signal(SIGCHLD, sig_handler_exec);
	signal(SIGPIPE, SIG_IGN);
//	start_new_jobs(jobs, rpipe);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);

	while (current)
	{
		current->envp = term->envp;
		current->argc = ft_strarrlen(current->argv);
//		ft_printf_fd(2, "argv[0]=%s j fd=%d\n", current->argv[0], jobs->fd_stdout);
//		redirect_process(current->fd_stdin, current->fd_stdout, current->fd_stderr);
		if (current->argv[0][0] == '\0') // temporary
			ft_putendl("EMPTY ARGV");
		else if (!is_builtin(current))
		{
//			signal(SIGPIPE, SIG_DFL);
			pid = fork();
			if (pid == 0)
				exit(exec_tprocess(current));
			current->pid = pid;
			waitpid(current->pid, &current->status, 0);
//			ft_printf("%s status=%d\n", current->argv[0], current->status);
		}
//		if (current->status)
//			break ;
		current = current->next;
//		set_pipeline_to_process(current, jobs, rpipe);
	}
	wait_children(jobs);
//	close(jobs->fd_stdout);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
}
