/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/13 22:55:49 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"
#include <sys/wait.h>

/*
** Handles the execution and pipe line creation of pipe operator.
** If there is other pipes in the command, traverses the tree
** and then executes the commands.
*/

static int	head_parent_is_and(t_node *current)
{
	while (current->parent)
		current = current->parent;
	return (current->operation == tkn_and);
}

t_job	*token_pipe(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	if (!current->left || (!job && !current->right))
		return (NULL);
	returnable = job;
	if (current->left->operation == tkn_pipe)
		returnable = tree_traversal(returnable, current->left, term);
	else if (!returnable
		|| (current->parent && current->parent->operation == tkn_and)
		|| (current->parent && head_parent_is_and(current)))
		returnable = pipe_start(returnable, term, current->left);
	else if (!current->right)
		returnable = pipe_end(returnable, term, current->left);
	else
		returnable = pipe_middle(returnable, term, current->left);
	if (current->right->operation == tkn_pipe)
		returnable = tree_traversal(returnable, current->right, term);
	else if (current->parent && current->parent->operation == tkn_pipe)
		returnable = pipe_middle(returnable, term, current->right);
	else
		returnable = pipe_end(returnable, term, current->right);
	return (returnable);
}
