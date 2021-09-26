/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_semi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 08:41:18 by hlaineka         ###   ########.fr       */
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
	run_non_recursive(left, current, term);
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
