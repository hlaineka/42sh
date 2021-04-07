/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/07 17:24:25 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_job	*token_pipe(t_job *job, t_node *current)
{
	t_job	*left;
	t_job	*right;
	t_job	*returnable;

	if (!current->left || !current->right || job)
		return (NULL);
	left = tree_traversal(current->left);
	right = tree_traversal(current->right);
	returnable = left;
	returnable->first_process->next = right->first_process;
	ft_free(right->command);
	ft_free(right);
	job = returnable;
	return (returnable);
}