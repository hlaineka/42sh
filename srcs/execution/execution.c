/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:28:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/19 14:29:48 by hhuhtane         ###   ########.fr       */
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

// start_new_jobs duplicates fds according to jobs structure.
// should it return int value to indicate if there was an error?

static void	start_new_jobs(t_job *jobs, int *rpipe)
{
	t_process	*current;

//	close(STDIN_FILENO);
//	close(STDOUT_FILENO);
//	close(STDERR_FILENO);
	dup2(jobs->fd_stdin, STDIN_FILENO);
	dup2(jobs->fd_stderr, STDERR_FILENO);
	close(jobs->fd_stdin);
	close(jobs->fd_stderr);
	current = jobs->first_process;
// If jobs have more than one processes
	if (current->next)
	{
		pipe(rpipe);
		dup2(rpipe[1], STDOUT_FILENO);
		close(rpipe[1]);
//		lpipe[0] = rpipe[0];
	}
	else
		dup2(jobs->fd_stdout, STDOUT_FILENO);
}

static void	set_pipeline_to_process(t_process *cur, t_job *jobs, int *rpipe)
{
	if (cur && cur->next)
	{
		dup2(rpipe[0], STDIN_FILENO);
		close(rpipe[0]);
		pipe(rpipe);
		dup2(rpipe[1], STDOUT_FILENO);
		close(rpipe[1]);
	}
	else if (cur)
	{
		dup2(rpipe[0], STDIN_FILENO);
		close(rpipe[0]);
		dup2(jobs->fd_stdout, STDOUT_FILENO);
	}
}

void	execute_jobs(t_job *jobs, t_term *term)
{
	t_process	*current;
	int			rpipe[2];

	while (jobs)
	{
		start_new_jobs(jobs, rpipe);
		current = jobs->first_process;
		while (current)
		{
			current->envp = term->envp;
			current->argc = ft_strarrlen(current->argv);
//			ft_printf_fd(2, "argv[0]=%s j fd=%d\n", current->argv[0], jobs->fd_stdout);
			if (!is_builtin(current))
			{
				current->status = exec_tprocess(current);
			}
			if (current->status)
				break ;
			current = current->next;
			set_pipeline_to_process(current, jobs, rpipe);
		}
		close(jobs->fd_stdout);
		jobs = jobs->next;
	}
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
}
