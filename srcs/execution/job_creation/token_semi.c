/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/01 12:27:52 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

/*
** Traverser the tree if necessary and executes the jobs when the semicolon
** operator is found. Traverses the tree recursively if there are more semicolon
** or pipe operators in the command.
*/

static void	get_right(t_node *current, t_term *term)
{
	t_job	*right;

	right = tree_traversal(NULL, current->right, term);
	if (right && current->right->operation != tkn_semi
		&& current->right->operation != tkn_pipe)
	{
		right->next = term->jobs;
		term->jobs = right;
		if (right->first_process->pid == 0)
			right->first_process->status = simple_command(right->first_process);
	}
}

t_job	*token_semi(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;

	left = NULL;
	if (!current->left || job)
		return (NULL);
	left = tree_traversal(NULL, current->left, term);
	if (left && current->left->operation != tkn_semi
		&& current->left->operation != tkn_pipe)
	{
		left->next = term->jobs;
		term->jobs = left;
		if (left->first_process->pid == 0)
			left->first_process->status = simple_command(left->first_process);
	}
	if (current->right)
		get_right(current, term);
	return (term->jobs);
}
