/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 11:14:06 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
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
	
	//(!job)
	//	->ensimmäinen pipe
	if (job || !current->left || !current->right)
		left = NULL;
	else
		left = job;
	right = NULL;
	if (!current->left || job)
		return (NULL);
	if (current->left)
	{
		// pipe left to right
		//fork
		left = tree_traversal(left, current->left, term);
		if (left)
		{
			left->next = term->jobs;
			term->jobs = left;
			execute_jobs(left, term);
		}
		//fork loppuu
	}
	if (current->right && current->right->operation == tkn_pipe)
		right = tree_traversal(right, current->right, term);
	else if (current->right)
	{
		//fork
		right = tree_traversal(right, current->right, term);
		if (right)
		{
			//tämä on viimeinen
			right->next = term->jobs;
			term->jobs = right;
			execute_jobs(right, term);
		}
		//fork loppuu
	}
	//yhdistä left ja righ
	return (term->jobs);
}