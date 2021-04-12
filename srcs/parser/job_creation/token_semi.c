/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/08 10:44:50 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_job	*token_semi(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;
	t_job	*right;
	t_job	*returnable;
	
	if ((!current->left && !current->right) || job)
		return (NULL);
	if (current->left)
		left = tree_traversal(current->left, term);
	if (current->right)
		right = tree_traversal(current->right, term);
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