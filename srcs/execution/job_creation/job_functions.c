/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:33:35 by hlaineka          #+#    #+#             */
/*   Updated: 2021/08/19 20:59:49 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"
#include "includes.h"
#include "job_control.h"

/*
** Helper functions for job creation.
*/

void	free_jobs(t_term *term)
{
	t_job		*job_to_free;
	t_job		*prev;

	job_to_free = term->jobs->next;
	prev = term->jobs;
	while (job_to_free)
	{
		if (is_job_completed(job_to_free) && job_to_free->notified)
		{
			if (job_to_free->next)
				prev->next = job_to_free->next;
			else
				prev->next = NULL;
			free_job(job_to_free);
			job_to_free = prev->next;
		}
		else
		{
			job_to_free = job_to_free->next;
			prev = prev->next;
		}
	}

/*
	t_job		*next;
	t_job		*job_to_free;
	t_job		*prev;

	job_to_free = term->jobs;
	prev = job_to_free;
	while (job_to_free)
	{
		next = job_to_free->next;
//		if (job_to_free->first_process->completed == 1
//			|| job_to_free->first_process->stopped == 1)
		if (is_job_completed(job_to_free))
		{
			if (prev == term->jobs)
			{
				term->jobs = job_to_free->next;
				prev = term->jobs;
			}
			else
				prev->next = job_to_free->next;
			free_job(job_to_free);
		}
		else
			prev = job_to_free;
		job_to_free = next;
	}
*/
}

void	free_job(t_job *job_to_free)
{
	t_process	*temp_process;
	t_process	*temp;

	temp_process = job_to_free->first_process;
	while (temp_process)
	{
		temp = temp_process->next;
		ft_strarray_free(temp_process->argv);
		temp_process->argv = NULL;
		if (temp_process->envp)
			ft_strarray_free(temp_process->envp);
		temp_process->envp = NULL;
		ft_free(temp_process);
		temp_process = NULL;
		temp_process = temp;
	}
	if (job_to_free->command)
	{
		ft_free(job_to_free->command);
		job_to_free->command = NULL;
	}
	ft_free(job_to_free);
	job_to_free = NULL;
}

t_job	*init_job(t_node *node)
{
	t_job		*returnable;
	t_process	*first_process;

	returnable = malloc(sizeof(t_job));
	first_process = malloc(sizeof(t_process));
	ft_bzero(returnable, sizeof(t_job));
	ft_bzero(first_process, sizeof(t_process));
	first_process->next = NULL;
	first_process->argv = malloc(ARGV_SIZE);
	ft_bzero(first_process->argv, ARGV_SIZE);
	first_process->envp = NULL;
	returnable->next = NULL;
	returnable->command = NULL;
	if (node)
		returnable->command = ft_strdup(node->full_command);
	returnable->first_process = first_process;
	returnable->fd_stdin = 0;
	returnable->fd_stdout = 1;
	returnable->fd_stderr = 2;
	return (returnable);
}

t_process	*init_process(t_term *term)
{
	t_process	*first_process;

	first_process = malloc(sizeof(t_process));
	ft_bzero(first_process, sizeof(t_process));
	first_process->term_ptr = term;
	first_process->next = NULL;
	first_process->argv = malloc(ARGV_SIZE);
	ft_bzero(first_process->argv, ARGV_SIZE);
	first_process->envp = NULL;
	return (first_process);
}

void	restore_fds(t_term *term)
{
	int	fd_status;

	if (term->intern_variables->flag_rawmode)
	{
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
	else
	{
		dup2(term->fd_stdin, STDIN_FILENO);
		dup2(term->fd_stdout, STDOUT_FILENO);
		dup2(term->fd_stderr, STDERR_FILENO);
	}
}
