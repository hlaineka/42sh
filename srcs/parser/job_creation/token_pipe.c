/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/28 10:53:55 by hlaineka         ###   ########.fr       */
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
	t_job		*left;
	t_job		*right;
	t_job		*returnable;

	if (!current->left || !current->right)
		return (NULL);
	left = tree_traversal(NULL, current->left, term);
	right = tree_traversal(NULL, current->right, term);
	if (job)
	{
		returnable = job;
		add_processes(returnable, left);
	}
	else
		returnable = left;
	add_processes(returnable, right);
	return (returnable);
}