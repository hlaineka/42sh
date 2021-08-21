/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:47:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/31 16:28:38 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

t_job	*token_and(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;

	left = NULL;
	if (!current->left || job)
		return (NULL);
	update_fds(term);
	left = tree_traversal(NULL, current->left, term);
	if (left && current->left->operation != tkn_semi
		&& current->left->operation != tkn_pipe
		&& current->left->operation != tkn_and 
		&& current->left->operation != tkn_and_if
		&& current->left->operation != tkn_or_if)
	{
		left->next = term->jobs->next;
		term->jobs->next = left;
		if (left->first_process->pid == 0)
		{
			//start process detached instead of next line
			left->bg = 1;
			left->first_process->status = simple_command(left->first_process, left, term);
		}
	}
	if (current->right)
		get_right(current, term);
	return (term->jobs->next);
}
