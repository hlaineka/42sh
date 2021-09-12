/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:47:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/12 14:54:48 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "ft_signal.h"

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
		return (NULL); //todo error
	if (pid == 0)
	{
		update_fds(term);
//		ft_printf("i'm child process\n");
		left = tree_traversal(left, current->left, term);
	}
	if (pid > 0)
	{
		left->first_process->pid = pid;
//		ft_printf("i'm parent process and i know child process id is %d\n", pid);
		setpgid(pid, 0);
		left->job_id = get_next_job_pgid(term->jobs->next);
		left->pgid = pid;
		set_signal_execution();
	}
//	left = tree_traversal(NULL, current->left, term);
	if (left && current->left->operation != tkn_semi
		&& current->left->operation != tkn_pipe
		&& current->left->operation != tkn_and 
		&& current->left->operation != tkn_and_if
		&& current->left->operation != tkn_or_if)
	{
		if (pid > 0)
		{
			left->next = term->jobs->next;
			term->jobs->next = left;
		}
		if (left->first_process->pid == 0 && pid == 0)
		{
			left->bg = 1;
			exit(simple_command(left->first_process, left, term));
		}
	}
	else if (pid == 0)
		exit(0);
	if (current->right)
		get_right(current, term);
	return (term->jobs->next);
}
