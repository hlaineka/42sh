/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:39:06 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 09:09:45 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

t_job	*token_and_if(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;

	left = NULL;
	if (!current->left || !current->right)
		return (NULL);
	update_fds(term);
	if (!job)
		left = tree_traversal(job, current->left, term);
	else
		left = tree_traversal(NULL, current->left, term);
	run_non_recursive(left, current, term);
	if (left->first_process->status == 0)
		get_right(current, term);
	return (term->jobs->next);
}
