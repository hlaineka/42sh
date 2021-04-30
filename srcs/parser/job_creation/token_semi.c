/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/30 09:18:25 by hlaineka         ###   ########.fr       */
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
	if (!current->left || job)
		return (NULL);
	left = tree_traversal(NULL, current->left, term);
	if (left)
	{
		left->next = term->jobs;
		term->jobs = left;
		if (left->first_process->pid == 0)
			simple_command(left->first_process);
	}
	if (current->right)
	{
		right = tree_traversal(NULL, current->right, term);
		if (right && current->right->operation != tkn_semi)
		{
			right->next = term->jobs;
			term->jobs = right;
			if (right->first_process->pid == 0)
				simple_command(right->first_process);
		}
	}
	return (term->jobs);
}