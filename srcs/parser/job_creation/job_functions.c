/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:33:35 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/06 16:32:12 by hlaineka         ###   ########.fr       */
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
	
	while (next_job)
	{
		temp_process = next_job->first_process;
		while (temp_process)
		{
			ft_strarray_free(temp_process->argv);
			temp = temp_process->next;
			ft_free(temp_process);
			temp_process = temp;
		}
		ft_free(next_job->command);
		temp_job = next_job->next;
		ft_free(next_job);
		next_job = temp_job;
	}
}

t_job	*init_job(void)
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
	returnable->next = NULL;
	returnable->command = NULL;
	returnable->first_process = first_process;
	return(returnable);
}
