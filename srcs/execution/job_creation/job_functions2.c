/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:41:23 by hlaineka          #+#    #+#             */
/*   Updated: 2021/10/02 19:28:54 by hlaineka         ###   ########.fr       */
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
		&& current->right->operation != tkn_pipe
		&& current->right->operation != tkn_and
		&& current->right->operation != tkn_and_if
		&& current->right->operation != tkn_or_if
		&& current->right->operation != tkn_assignment)
	{
		right->next = term->jobs->next;
		term->jobs->next = right;
	}
	if (right->first_process->pid == 0)
		right->first_process->status = simple_command(right->first_process,
			right, term);
}

int	run_non_recursive(t_job *job, t_node *current, t_term *term)
{
	if (job && current->left->operation != tkn_semi
		&& current->left->operation != tkn_pipe
		&& current->left->operation != tkn_and
		&& current->left->operation != tkn_and_if
		&& current->left->operation != tkn_or_if
		&& current->left->operation != tkn_assignment)
	{
		job->next = term->jobs->next;
		term->jobs->next = job;
		if (job->first_process->pid == 0)
			job->first_process->status = simple_command(job->first_process,
					job, term);
	}
	return (0);
}

static void	restore_rawmode_fds(t_term *term)
{
	int	fd_status;

	fd_status = check_fd(0, 0);
	if (-1 != fd_status)
		close(0);
	dup(term->fd_stdin);
	dup2(0, STDIN_FILENO);
	fd_status = check_fd(1, 0);
	if (-1 != fd_status)
		close(1);
	dup(term->fd_stdout);
	dup2(1, STDOUT_FILENO);
	fd_status = check_fd(2, 0);
	if (-1 != fd_status)
		close(2);
	dup(term->fd_stderr);
	dup2(2, STDERR_FILENO);
	if (term->heredoc_fd != -1)
		close(term->heredoc_fd);
}

void	restore_fds(t_term *term)
{
	if (term->intern_variables->flag_rawmode)
		restore_rawmode_fds(term);
	else
	{
		dup2(term->fd_stdin, STDIN_FILENO);
		dup2(term->fd_stdout, STDOUT_FILENO);
		dup2(term->fd_stderr, STDERR_FILENO);
	}
}
