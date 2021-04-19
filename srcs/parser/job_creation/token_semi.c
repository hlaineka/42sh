/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/16 12:26:08 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_job	*add_job(t_job *first, t_job *last)
{
	t_job	*temp;
	t_job	*returnable;

	returnable = NULL;
	if (first)
	{
		temp = first;
		while (temp->next)
			temp = temp->next;
		temp->next = last;
		returnable = first;
	}
	else
		returnable = last;
	return (returnable);
}

t_job	*token_semi(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;
	t_job	*right;
	t_job	*returnable;
	
	left = NULL;
	right = NULL;
	returnable = NULL;
	if (current->left)
		left = tree_traversal(NULL, current->left, term);
	if (current->right)
		right = tree_traversal(NULL, current->right, term);
	returnable = add_job(job, left);
	returnable = add_job(returnable, right);
	return (returnable);
}