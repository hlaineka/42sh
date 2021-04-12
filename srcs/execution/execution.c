/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:28:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/12 15:11:15 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/*
static void	set_read(int* lpipe)
{
	dup2(lpipe[0], STDIN_FILENO);
	close(lpipe[0]); // we have a copy already, so close it
//	close(lpipe[1]); // not using this end
}

static void	set_write(int* rpipe)
{
	dup2(rpipe[1], STDOUT_FILENO);
//	close(rpipe[0]); // not using this end
	close(rpipe[1]); // we have a copy already, so close it
}

static void	chain_pipes(int *lpipe, int *rpipe)
{
	if (lpipe)
		set_read(lpipe);
	if (rpipe)
		set_write(rpipe);
}
*/

void	execute_jobs(t_job *jobs, t_term *term)
{
	t_process	*current;
	int			lpipe[2];
	int			rpipe[2];

	while (jobs)
	{

		dup2(jobs->fd_stdin, STDIN_FILENO);
//		dup2(jobs->fd_stdout, STDOUT_FILENO);
		dup2(jobs->fd_stderr, STDERR_FILENO);
/*
		close(jobs->fd_stdin);
		close(jobs->fd_stdout);
		close(jobs->fd_stderr);
*/
		current = jobs->first_process;

		if (current->next)
		{
			pipe(rpipe);
			dup2(rpipe[1], STDOUT_FILENO);
			close(rpipe[1]);
			lpipe[0] = rpipe[0];
/*
			pipe(rpipe);
			chain_pipes(NULL, rpipe);
			lpipe[0] = rpipe[0];
			lpipe[1] = rpipe[1];
*/
		}
		else
		{
/*
			dup2(term->fd_stdin, STDIN_FILENO);
			dup2(term->fd_stdout, STDOUT_FILENO);
			dup2(term->fd_stderr, STDERR_FILENO);
*/
// USE THIS WHEN THEY WORK
//			dup2(jobs->fd_stdin, STDIN_FILENO);
			dup2(jobs->fd_stdout, STDOUT_FILENO);
//			dup2(jobs->fd_stderr, STDERR_FILENO);

		}

/*
		pipe(rpipe);
		dup2(rpipe[1], STDOUT_FILENO);
		close(rpipe[0]);
		close(rpipe[1]);
*/

		while (current)
		{
			current->envp = term->envp;
			current->argc = ft_strarrlen(current->argv);
//			ft_putendl_fd("t1x", 2);
			if (!is_builtin(current))
			{
//				ft_putendl_fd("exec function stuff here", term->fd_stdout);
				current->status = exec_tprocess(current);
//				ft_putendl_fd("execin jalkeen", 2);
			}
//			current->envp = NULL;
			current = current->next;
			if (current && current->next)
			{
//				ft_putendl_fd("execin jalkeen", 2);
				dup2(lpipe[0], STDIN_FILENO);
				close(lpipe[0]);
				pipe(rpipe);
				dup2(rpipe[1], STDOUT_FILENO);
				close(rpipe[1]);
				lpipe[0] = rpipe[0];

//				chain_pipes(lpipe, rpipe);
//				lpipe[0] = rpipe[0];
//				lpipe[1] = rpipe[1];
			}
			else if (current)
			{
				dup2(lpipe[0], STDIN_FILENO);
				close(lpipe[0]);
//				ft_putendl_fd("elsessa", STDOUT_FILENO);
//				ft_putendl_fd("elsessa", 2);

//				chain_pipes(lpipe, NULL);

//				ft_putendl_fd("elsessa", 2);

				dup2(jobs->fd_stdout, STDOUT_FILENO);
//				dup2(term->fd_stdout, STDOUT_FILENO);

//				lpipe[0] = rpipe[0];
//				lpipe[1] = rpipe[1];
			}
/*
			else
			{
				close(lpipe[0]);
				close(lpipe[1]);
			}
*/
		}
		dup2(term->fd_stdin, STDIN_FILENO);
		dup2(term->fd_stdout, STDOUT_FILENO);
		dup2(term->fd_stderr, STDERR_FILENO);
		close(jobs->fd_stdin);
		close(jobs->fd_stdout);
		close(jobs->fd_stderr);
		// do we need to return fds to normal?
		jobs = jobs->next;
	}
}
