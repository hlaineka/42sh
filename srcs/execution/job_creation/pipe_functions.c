/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 11:26:20 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 11:36:46 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"
#include <sys/wait.h>
#include <signal.h>
#include "ft_signal.h"

void	execute_child(t_job *job, t_node *current, t_term *term)
{
	job = tree_traversal(job, current, term);
	if (job)
	{
		simple_command_pipe(job->first_process, term);
		exit(job->first_process->status);
	}
	exit(1);
}

t_job	*pipe_start(t_job *job, t_term *term, t_node *current)
{
	t_process	*temp_process;
	int			rpipe[2];

	set_signal_execution();
	if (!job)
	{
		job = init_job(current);
		job->next = term->jobs->next;
		term->jobs->next = job;
	}
	temp_process = job->first_process;
	pipe(rpipe);
	temp_process->pid = fork_and_chain_pipes(NULL, rpipe);
	setpgid(temp_process->pid, 0);
	if (temp_process->pid == 0)
		execute_child(job, current, term);
	if (!job->bg)
		tcsetpgrp(term->fd_stderr, temp_process->pid);
	job->job_id = get_next_job_pgid(term->jobs->next);
	job->pgid = temp_process->pid;
	job->fd_stdin = rpipe[0];
	job->fd_stdout = rpipe[1];
	return (job);
}

t_job	*pipe_middle(t_job *job, t_term *term, t_node *current)
{
	t_process	*temp_process;
	int			lpipe[2];
	int			rpipe[2];

	temp_process = init_process(term);
	temp_process->next = job->first_process;
	job->first_process = temp_process;
	lpipe[0] = job->fd_stdin;
	lpipe[1] = job->fd_stdout;
	pipe(rpipe);
	temp_process->pid = fork_and_chain_pipes(lpipe, rpipe);
	if (temp_process->pid == 0)
	{
		setpgid(0, job->pgid);
		execute_child(job, current, term);
	}
	setpgid(temp_process->pid, job->pgid);
	close(job->fd_stdout);
	close(job->fd_stdin);
	job->fd_stdin = rpipe[0];
	job->fd_stdout = rpipe[1];
	return (job);
}

static void	set_standards_back(t_term *term)
{
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
}

t_job	*pipe_end(t_job *job, t_term *term, t_node *current)
{
	t_process	*temp_process;
	int			lpipe[2];

	temp_process = init_process(term);
	temp_process->next = job->first_process;
	job->first_process = temp_process;
	lpipe[0] = job->fd_stdin;
	lpipe[1] = job->fd_stdout;
	temp_process->pid = fork_and_chain_pipes(lpipe, NULL);
	setpgid(temp_process->pid, job->pgid);
	if (temp_process->pid == 0)
		execute_child(job, current, term);
	close(lpipe[0]);
	close(lpipe[1]);
	close(job->fd_stderr);
	wait_job_and_get_status(job, term);
	if (!job->bg)
	{
		job->notified = 1;
		tcsetpgrp(term->fd_stderr, getpgrp());
	}
	set_standards_back(term);
	if (job->bg)
		exit(term->last_return);
	return (job);
}
