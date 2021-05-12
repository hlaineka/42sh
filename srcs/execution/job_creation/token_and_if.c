/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:39:06 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/12 10:42:02 by hlaineka         ###   ########.fr       */
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
	if (left && current->left->operation != tkn_semi
		&& current->left->operation != tkn_pipe)
	{
		left->next = term->jobs;
		term->jobs = left;
		if (left->first_process->pid == 0)
			left->first_process->status = simple_command(left->first_process);
	}
	if (left->first_process->status == 0)
		get_right(current, term);
	return (term->jobs);
}
