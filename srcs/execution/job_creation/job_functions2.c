/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:41:23 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/27 17:03:41 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

/*
** Updates fds back between jobs.
*/

void	update_fds(t_term *term)
{
	if (-1 != check_fd(0, 0))
		close(0);
	dup(term->fd_stdin);
	if (-1 != check_fd(1, 0))
		close(1);
	dup(term->fd_stdout);
	if (-1 != check_fd(2, 0))
		close(2);
	dup(term->fd_stderr);
}

/*
** Used by semi, and_if and or_if
*/

void	get_right(t_node *current, t_term *term)
{
	t_job	*right;

	update_fds(term);
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
