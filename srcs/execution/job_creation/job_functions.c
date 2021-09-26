/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:33:35 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 09:07:11 by hlaineka         ###   ########.fr       */
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
