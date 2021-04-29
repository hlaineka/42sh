/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:33:35 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 18:58:21 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "includes.h"

void	free_jobs(t_job *next_job)
{
	t_process	*temp_process;
	t_process	*temp;
	t_job		*temp_job;
	t_job		*job_to_free;
	
	job_to_free = next_job;
	while (job_to_free)
	{
		temp_job = job_to_free->next;
		if (job_to_free->first_process->completed == 1 || job_to_free->first_process->stopped == 1)
		{
			close(job_to_free->fd_stdin);
			close(job_to_free->fd_stdout);
			close(job_to_free->fd_stderr);
			temp_process = job_to_free->first_process;
			while (temp_process)
			{
				close(temp_process->fd_stdin);
				close(temp_process->fd_stdout);
				close(temp_process->fd_stderr);
				ft_strarray_free(temp_process->argv);
				temp = temp_process->next;
				ft_free(temp_process);
				temp_process = temp;
			}
			ft_free(job_to_free->command);
			ft_free(job_to_free);
		}
		job_to_free = temp_job;
	}
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
	returnable->first_process->fd_stdin = dup(STDIN_FILENO);
	returnable->first_process->fd_stdout = dup(STDOUT_FILENO);
	returnable->first_process->fd_stderr = dup(STDERR_FILENO);
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
	first_process->fd_stdin = dup(STDIN_FILENO);
	first_process->fd_stdout = dup(STDOUT_FILENO);
	first_process->fd_stderr = dup(STDERR_FILENO);
	return (first_process);
}
