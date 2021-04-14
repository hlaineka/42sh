/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/14 12:21:11 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_job	*token_pipe(t_job *job, t_term *term, t_node *current)
{
	t_job		*left;
	t_job		*right;
	t_job		*returnable;
	t_process	*temp;

	if (!current->left || !current->right || job)
		return (NULL);
	left = tree_traversal(current->left, term);
	right = tree_traversal(current->right, term);
	returnable = left;
	temp = returnable->first_process;
	while (temp->next)
		temp = temp->next;
	temp->next = right->first_process;
	ft_free(right->command);
	close(right->fd_stdin);
	close(right->fd_stdout);
	close(right->fd_stderr);
	ft_free(right);
	job = returnable;
	return (returnable);
}