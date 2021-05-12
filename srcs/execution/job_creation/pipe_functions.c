/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 11:26:20 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/10 20:04:35 by hhuhtane         ###   ########.fr       */
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
		simple_command(job->first_process);
		exit(job->first_process->status);
	}
	exit(1);
}

t_job	*pipe_start(t_job *job, t_term *term, t_node *current)
{
	t_process	*temp_process;
	int			rpipe[2];

	job = init_job(term);
	job->next = term->jobs;
	term->jobs = job;
	temp_process = job->first_process;
	pipe(rpipe);
	temp_process->pid = fork_and_chain_pipes(NULL, rpipe);
	if (temp_process->pid == 0)
		execute_child(job, current, term);
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
		execute_child(job, current, term);
	close(job->fd_stdout);
	close(job->fd_stdin);
	job->fd_stdin = rpipe[0];
	job->fd_stdout = rpipe[1];
	return (job);
}

static void	wait_till_ready(t_job *job)
{
	t_process	*proc;
	int			status;

	proc = job->first_process;
	while (proc)
	{
		waitpid(proc->pid, &status, WUNTRACED);
		get_status_and_condition(proc, status);
		proc = proc->next;
	}
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
	if (temp_process->pid == 0)
		execute_child(job, current, term);
	close(lpipe[0]);
	close(lpipe[1]);
	close(job->fd_stderr);
	signal(SIGINT, sig_handler_exec);
	wait_till_ready(job);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
	return (job);
}
