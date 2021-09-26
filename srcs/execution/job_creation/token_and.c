/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:47:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 11:07:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "ft_signal.h"

static void	parent_duties(t_term *term, t_job *left, int pid)
{
	update_fds(term);
	left->first_process->pid = pid;
	setpgid(pid, 0);
	left->job_id = get_next_job_pgid(term->jobs->next);
	left->pgid = pid;
	set_signal_execution();
}

static void	run_command_child(t_job *left, t_node *current, int pid,
	t_term *term)
{
	if (left && current->left->operation != tkn_semi
		&& current->left->operation != tkn_and
		&& current->left->operation != tkn_and_if
		&& current->left->operation != tkn_or_if
		&& current->left->operation != tkn_assignment)
	{
		if (pid > 0)
		{
			left->next = term->jobs->next;
			term->jobs->next = left;
		}
		if (left->first_process->pid == 0 && pid == 0)
			exit(simple_command(left->first_process, left, term));
	}
}

t_job	*token_and(t_job *job, t_term *term, t_node *current)
{
	t_job	*left;
	pid_t	pid;

	left = NULL;
	if (!current->left || job)
		return (NULL);
	left = init_job(current);
	pid = fork();
	if (pid < 0)
		return (NULL);
	if (pid == 0)
	{
		left->bg = 1;
		left = tree_traversal(left, current->left, term);
	}
	if (pid > 0)
		parent_duties(term, left, pid);
	run_command_child(left, current, pid, term);
	if (pid == 0)
		exit(0);
	if (current->right)
		get_right(current, term);
	return (term->jobs->next);
}
