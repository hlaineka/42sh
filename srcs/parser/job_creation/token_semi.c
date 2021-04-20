/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/20 19:25:17 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

t_job	*token_semi(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;
	t_job	*right;
	
	left = NULL;
	right = NULL;
	if (job)
		return (NULL);
	if (current->left)
	{
		left = tree_traversal(NULL, current->left, term);
		if (left)
			execute_jobs(left, term);
	}
	if (current->right)
	{
		right = tree_traversal(NULL, current->right, term);
		if (right)
			execute_jobs(right, term);
	}
	return (NULL);
}