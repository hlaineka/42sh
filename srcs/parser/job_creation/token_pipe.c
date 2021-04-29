/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 19:19:48 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"
#include <sys/wait.h>

void	add_processes(t_job *returnable, t_job *removable)
{
	t_process	*temp;
	
	if (!removable)
		return;
	if (returnable->first_process)
	{
		temp = returnable->first_process;
		while (temp->next)
			temp = temp->next;
		temp->next = removable->first_process;
	}
	else
		returnable->first_process = removable->first_process;
	close(removable->fd_stdin);
	close(removable->fd_stdout);
	close(removable->fd_stderr);
	ft_free(removable->command);
	ft_free(removable);
}

t_job	*token_pipe(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;
	t_job	*right;
	int		lpipe[2];
	int		rpipe[2];
	t_process	*temp_process;
	
	if (!current->left || !current->right)
		return (NULL);
	left = job;
	right = NULL;
	if (current->left)
	{
		if (left)
		{
			temp_process = init_process(term);
			temp_process->next = left->first_process;
			left->first_process = temp_process;
			lpipe[0] = left->fd_stdin;
			lpipe[1] = left->fd_stdout;
			pipe(rpipe);
			temp_process->pid = fork_and_chain_pipes(lpipe, rpipe);
		}
		else
		{
			left = init_job(term);
			left->next = term->jobs;
			term->jobs = left;
			temp_process = left->first_process;
			pipe(rpipe);
			temp_process->pid = fork_and_chain_pipes(NULL, rpipe);
		}
		//if (left->first_process->pid < 0)
		//	fail
		if (temp_process->pid == 0)
		{
			left = tree_traversal(left, current->left, term);
			if (left)
			{
				simple_command(left->first_process);
				exit(left->first_process->status);
			}
			exit(1);
		}
		left->fd_stdin = rpipe[0];
		left->fd_stdout = rpipe[1];
	}
	if (current->right && current->right->operation == tkn_pipe)
		right = tree_traversal(left, current->right, term);
	else if (current->right)
	{
		temp_process = init_process(term);
		temp_process->next = left->first_process;
		left->first_process = temp_process;
		lpipe[0] = rpipe[0];
		lpipe[1] = rpipe[1];
		temp_process->pid = fork_and_chain_pipes(lpipe, NULL);
		if (temp_process->pid == 0)
		{
			dup2(term->fd_stdout, STDOUT_FILENO);
			right = tree_traversal(NULL, current->right, term);
			if (right)
			{
				simple_command(right->first_process);
				exit(right->first_process->status);
			}
			exit(1);
		}
		waitpid(temp_process->pid, &temp_process->status, 0);
		dup2(term->fd_stdout, STDOUT_FILENO);
		dup2(term->fd_stdin, STDIN_FILENO);
		dup2(term->fd_stderr, STDERR_FILENO);
		//left->fd_stdin = term->fd_stdin;
		//left->fd_stdout = term->fd_stdout;
		//close(lpipe[0]);
		//close(lpipe[1]);
		//lpipe[0] = rpipe[0];
		//lpipe[1] = rpipe[1];
	}
	return (left);
}