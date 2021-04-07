/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/07 14:42:44 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_job	*token_semi(t_job *job, t_node *current)
{
	t_job	*left;
	t_job	*right;
	t_job	*returnable;
	
	if ((!current->left && !current->right) || job)
		return (NULL);
	if (current->left)
		left = tree_traversal(current->left);
	if (current->right)
		right = tree_traversal(current->right);
	if (!current->left)
		returnable = right;
	else
	{
		returnable = left;
		returnable->next = right;
	}
	job = returnable;
	return (returnable);
}