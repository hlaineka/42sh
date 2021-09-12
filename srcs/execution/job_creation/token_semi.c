/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/12 10:07:09 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

/*
** Traverser the tree if necessary and executes the jobs when the semicolon
** operator is found. Traverses the tree recursively if there are more semicolon
** or pipe operators in the command.
*/

t_job	*token_semi(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;

	left = NULL;
	if (job)
		return (NULL);
	update_fds(term);
	if (current->left)
		left = tree_traversal(NULL, current->left, term);
	if (left && current->left->operation != tkn_semi
		&& current->left->operation != tkn_pipe
		&& current->left->operation != tkn_and 
		&& current->left->operation != tkn_and_if
		&& current->left->operation != tkn_or_if
		&& current->left->operation != tkn_assignment_word)
	{
		left->next = term->jobs->next;
		term->jobs->next = left;
		if (left->first_process->pid == 0)
			left->first_process->status = simple_command(left->first_process, left, term);
	}
	if (!left)
	{
		left = init_job(NULL);
		left->first_process->pid = -1;
		left->next = term->jobs->next;
		term->jobs->next = left;
	}
	if (current->right)
		get_right(current, term);
	return (term->jobs->next);
}
