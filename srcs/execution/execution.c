/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:28:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/09 14:18:33 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	set_read(int* lpipe)
{
	dup2(lpipe[0], STDIN_FILENO);
	close(lpipe[0]); // we have a copy already, so close it
	close(lpipe[1]); // not using this end
}

static void	set_write(int* rpipe)
{
	dup2(rpipe[1], STDOUT_FILENO);
	close(rpipe[0]); // not using this end
	close(rpipe[1]); // we have a copy already, so close it
}

static void	chain_pipes(int *lpipe, int *rpipe)
{
	if (lpipe)
		set_read(lpipe);
	if (rpipe)
		set_write(rpipe);
}

void	execute_jobs(t_job *jobs, t_term *term)
{
	t_process	*current;
	int			lpipe[2];
	int			rpipe[2];

	while (jobs)
	{
		dup2(jobs->fd_stdin, STDIN_FILENO);
		dup2(jobs->fd_stdout, STDOUT_FILENO);
		dup2(jobs->fd_stderr, STDERR_FILENO);
		// change original fds?
		current = jobs->first_process;
		if (current->next)
		{
			pipe(rpipe);
			chain_pipes(NULL, rpipe);
			lpipe[0] = rpipe[0];
			lpipe[1] = rpipe[1];
		}
		while (current)
		{
			current->envp = term->envp;
			current->argc = ft_strarrlen(current->argv);
			if (!is_builtin(current))
			{
				ft_putendl("exec function stuff here");
				current->status = exec_tprocess(current);
			}
//			current->envp = NULL;
			current = current->next;
			if (current && current->next)
			{
				chain_pipes(lpipe, rpipe);
				lpipe[0] = rpipe[0];
				lpipe[1] = rpipe[1];
			}
			else
			{
				chain_pipes(lpipe, NULL);
				dup2(term->fd_stdout, jobs->fd_stdout);
//				lpipe[0] = rpipe[0];
//				lpipe[1] = rpipe[1];
			}
		}
		dup2(term->fd_stdin, STDIN_FILENO);
		dup2(term->fd_stdout, STDOUT_FILENO);
		dup2(term->fd_stderr, STDERR_FILENO);
		// do we need to return fds to normal?
		jobs = jobs->next;
	}
}
