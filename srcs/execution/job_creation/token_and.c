/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:47:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/06/30 22:05:18 by hlaineka         ###   ########.fr       */
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
		&& current->left->operation != tkn_and)
	{
		left->next = term->jobs;
		term->jobs = left;
		if (left->first_process->pid == 0)
		{
			//start process detached instead of next line
			// set variable that shows to be run in background
			left->first_process->status = simple_command(left->first_process, term);
		}
	}
	if (current->right)
		get_right(current, term);
	return (term->jobs);
}
