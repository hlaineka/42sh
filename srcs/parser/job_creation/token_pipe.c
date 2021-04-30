/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/30 09:00:11 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"
#include <sys/wait.h>

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
	{
		job = tree_traversal(job, current, term);
		//ft_printf_fd(term->fd_stdout, "%s\r\n", job->first_process->argv[0]);
		if (job)
		{
			simple_command(job->first_process);
			exit(job->first_process->status);
		}
		exit(1);
	}
	close(job->fd_stdout);
	close(job->fd_stdin);
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
		job = tree_traversal(job, current, term);
		//ft_printf_fd(term->fd_stdout, "%s\r\n", job->first_process->argv[0]);
		if (job)
		{
			simple_command(job->first_process);
			exit(job->first_process->status);
		}
		exit(1);
	}
	close(job->fd_stdout);
	close(job->fd_stdin);
	job->fd_stdin = rpipe[0];
	job->fd_stdout = rpipe[1];
	return (job);
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
	{
		dup2(term->fd_stdout, STDOUT_FILENO);
		job = tree_traversal(NULL, current, term);
		if (job)
		{
			//ft_printf_fd(term->fd_stdout, "%s\r\n", job->first_process->argv[0]);
			simple_command(job->first_process);
			exit(job->first_process->status);
		}
		exit(1);
	}
	close(lpipe[0]);
	close(lpipe[1]);
	waitpid(temp_process->pid, &temp_process->status, 0);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
	return (job);
}

t_job	*token_pipe(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;
	
	if (!current->left || (!job && !current->right))
	{	
		//ft_printf("error\r\n");
		return (NULL);
	}
	returnable = job;
	if (current->left->operation == tkn_pipe)
	{	
		//ft_printf("tree traversal left\r\n");
		returnable = tree_traversal(returnable, current->left, term);
	}
	else if (!returnable)
	{	
		//ft_printf("pipe start left\r\n");
		returnable = pipe_start(returnable, term, current->left);
	}
	else if (!current->right)
	{	
		//ft_printf("pipe end left\r\n");
		returnable = pipe_end(returnable, term, current->left);
	}
	else
	{	
		//ft_printf("pipe middle left\r\n");
		returnable = pipe_middle(returnable, term, current->left);
	}
	if (current->right->operation == tkn_pipe)
	{	
		//ft_printf("tree traversal right\r\n");
		returnable = tree_traversal(returnable, current->right, term);
	}
	else if (current->parent && current->parent->operation == tkn_pipe)
	{	
		//ft_printf("pipe middle right\r\n");
		returnable = pipe_middle(returnable, term, current->right);
	}
	else
	{	
		//ft_printf("pipe end right\r\n");
		returnable = pipe_end(returnable, term, current->right);
	}
	
	return (returnable);
}