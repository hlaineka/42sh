/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 13:55:27 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"

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
		left = NULL;
	left = job;
	right = NULL;
	if (current->left)
	{
		pipe(rpipe);
		if (left)
		{
			lpipe[0] = left->fd_stdout;
			lpipe[1] = left->fd_stdin;
			temp_process = init_process(term);
			temp_process->next = left->first_process;
			left->first_process = temp_process;
			left->first_process->pid = fork_and_chain_pipes(lpipe, rpipe);
		}
		else
		{
			left = init_job(term);
			left->next = g_term->jobs;
			g_term->jobs = left;
			left->first_process->pid = fork_and_chain_pipes(NULL, rpipe);
		}
		left = tree_traversal(left, current->left, term);
		if (left)
		{
			temp_process = left->first_process;
			temp_process->status = simple_command(temp_process);
			temp_process->completed = 1;
			left->fd_stdout = rpipe[0];
			left->fd_stdin = rpipe[1];
			exit(left->first_process->status);
		}
		exit(1);
	}
	if (current->right && current->operation == tkn_pipe)
		right = tree_traversal(right, current->right, term);
	else if (current->right)
	{
		pipe(rpipe); //This is not needed?
		left = g_term->jobs; //does this work? is the left already saved here?
		lpipe[0] = left->fd_stdout;
		lpipe[1] = left->fd_stdin;
		right = init_job(term);
		right->first_process->pid = fork_and_chain_pipes(lpipe, NULL);
		right = tree_traversal(right, current->right, term);
		right->first_process->next = left->first_process;
		left->first_process = right->first_process;
		//delete right job but not the processes
		close(lpipe[0]);
		close(lpipe[1]);
		lpipe[0] = rpipe[0];
		lpipe[1] = rpipe[1];
		if (right)
		{
			temp_process = left->first_process;
			temp_process->status = simple_command(temp_process);
			temp_process->completed = 1;
			g_term->jobs->fd_stdout = rpipe[0];
			g_term->jobs->fd_stdin = rpipe[1];
			exit(temp_process->status);
		}
		exit(1);
	}
	return (term->jobs);
}