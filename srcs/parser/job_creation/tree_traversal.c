/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:58:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/06 16:52:42 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"

t_job	*tree_traversal(t_node *current, t_job	*(**op_functions)(t_job *job, t_node *current), t_job *first_job)
{
	t_job	*returnable;

	returnable = first_job;
	if (!current->left && !current->right)
		return (returnable);
	if (current->left)
		returnable = tree_traversal(current->left, op_functions, returnable);
	if (current->right)
		returnable = tree_traversal(current->right, op_functions, returnable);
	if (op_functions[current->operation])
		returnable = op_functions[current->operation](returnable, current);
	return (returnable);
}