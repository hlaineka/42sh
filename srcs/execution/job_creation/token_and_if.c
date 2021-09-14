/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:39:06 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/12 18:27:00 by hlaineka         ###   ########.fr       */
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
	ft_printf("token_and_if: before left tree traversal\n");
	if (!job)
		left = tree_traversal(job, current->left, term);
	else
		left = tree_traversal(NULL, current->left, term);
	ft_printf("token_and_if: after left tree traversal\n");
	if (left && current->left->operation != tkn_semi
		&& current->left->operation != tkn_pipe
		&& current->left->operation != tkn_and 
		&& current->left->operation != tkn_and_if
		&& current->left->operation != tkn_or_if
		&& current->left->operation != tkn_assignment)
	{
		left->next = term->jobs->next;
		term->jobs->next = left;
		if (left->first_process->pid == 0)
			left->first_process->status = simple_command(left->first_process, left, term);
	}
	ft_printf("token_and_if: before right tree traversal\n");
	if (left->first_process->status == 0)
		get_right(current, term);
	ft_printf("token_and_if: after right tree traversal\n");
	while(1);
	return (term->jobs->next);
}
