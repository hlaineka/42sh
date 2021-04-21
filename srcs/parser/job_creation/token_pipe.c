/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/21 09:33:55 by hlaineka         ###   ########.fr       */
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
	left = init_job();
	right = init_job();
	//pipe(left, right);
	left = tree_traversal(left, current->left, term);
	right = tree_traversal(right, current->right, term);
	returnable = left;
	if (returnable->first_process)
	{
		temp = returnable->first_process;
		while (temp->next)
			temp = temp->next;
		temp->next = right->first_process;
	}
	else
		returnable->first_process = right->first_process;
	close(right->fd_stdin);
	close(right->fd_stdout);
	close(right->fd_stderr);
	ft_free(right->command);
	ft_free(right);
	job = returnable;
	return (returnable);
}