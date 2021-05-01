/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:33:35 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/01 09:56:48 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"
#include "includes.h"

void	free_jobs(t_term *term)
{
	t_job		*next;
	t_job		*job_to_free;
	t_job		*prev;
	
	job_to_free = term->jobs;
	prev = job_to_free;
	while (job_to_free)
	{
		next = job_to_free->next;
		if (job_to_free->first_process->completed == 1 || job_to_free->first_process->stopped == 1)
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
}

void	free_job(t_job *job_to_free)
{
	t_process	*temp_process;
	t_process	*temp;
	
	close(job_to_free->fd_stdin);
	close(job_to_free->fd_stdout);
	close(job_to_free->fd_stderr);
	temp_process = job_to_free->first_process;
	while (temp_process)
	{
		temp = temp_process->next;
		ft_strarray_free(temp_process->argv);
		temp_process->argv = NULL;
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

t_job	*init_job(t_term *term)
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
	first_process->envp = term->envp;
	returnable->next = NULL;
	returnable->command = NULL;
	returnable->first_process = first_process;
	returnable->fd_stdin = dup(STDIN_FILENO);
	returnable->fd_stdout = dup(STDOUT_FILENO);
	returnable->fd_stderr = dup(STDERR_FILENO);
	return(returnable);
}

t_process	*init_process(t_term *term)
{
	t_process	*first_process;

	first_process = malloc(sizeof(t_process));
	ft_bzero(first_process, sizeof(t_process));
	first_process->next = NULL;
	first_process->argv = malloc(ARGV_SIZE);
	ft_bzero(first_process->argv, ARGV_SIZE);
	first_process->envp = ft_strarr_copy(term->envp);
	return (first_process);
}

void	restore_fds(t_term *term)
{
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
}
