/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:40:47 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/07 17:32:20 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"

static void	debug_printing(t_job *next_job)
{
	int			i;
	t_job		*temp_job;
	t_process	*temp_process;
	int			jobs;
	int			processes;

	i = 0;
	jobs = 1;
	processes = 1;
	temp_job = next_job;
	while (temp_job)
	{
		ft_printf("the %i job:\n", jobs);
		temp_process = temp_job->first_process;
		processes = 1;
		while (temp_process)
		{
			ft_printf("argv of the %i process: ", processes);
			i = 0;
			while (temp_process->argv[i])
			{
				ft_printf("%s, ", temp_process->argv[i]);
				i++;
			}
			ft_printf("\n");
			temp_process = temp_process->next;
			processes++;
		}
		temp_job = temp_job->next;
		jobs++;
	}
}

t_job	*job_creation(t_node *root, bool debug)
{
	t_job	*returnable;

	if (!root)
		return (NULL);
	returnable = tree_traversal(root);
	if (returnable == NULL)
		ft_printf_fd(2, "syntax_error\n");
	if (debug)
		debug_printing(returnable);
	return (returnable);
}
