/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:40:47 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/12 10:41:50 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "includes.h"

static void	debug_print_process(t_process *temp_process, int processes)
{
	int			i;

	if (temp_process->completed == 1)
		ft_printf_fd(STDOUT_FILENO, "completed. ");
	if (temp_process->stopped == 1)
		ft_printf_fd(STDOUT_FILENO, "stopped. ");
	ft_printf_fd(STDOUT_FILENO, "argv of the %i process: ", processes);
	i = 0;
	while (temp_process->argv && temp_process->argv[i])
	{
		ft_printf_fd(STDOUT_FILENO, "%s, ", temp_process->argv[i]);
		i++;
	}
	ft_printf_fd(STDOUT_FILENO, "\n");
}

static void	debug_printing(t_job *next_job)
{
	t_job		*temp_job;
	t_process	*temp_process;
	int			jobs;
	int			processes;

	jobs = 1;
	processes = 1;
	temp_job = next_job;
	while (temp_job)
	{
		ft_printf_fd(STDOUT_FILENO, "the %i job:\n", jobs);
		temp_process = temp_job->first_process;
		processes = 1;
		while (temp_process)
		{
			debug_print_process(temp_process, processes);
			temp_process = temp_process->next;
			processes++;
		}
		temp_job = temp_job->next;
		jobs++;
	}
}

t_job	*job_creation(t_node *root, t_term *term)
{
	t_job	*returnable;

	if (!root)
		return (NULL);
	returnable = tree_traversal(NULL, root, term);
	if (returnable == NULL)
		ft_printf_fd(STDERR_FILENO, "job syntax_error\n");
	if (returnable && returnable->first_process->pid == 0)
	{
		returnable->next = term->jobs;
		term->jobs = returnable;
		returnable->first_process->status
			= simple_command(returnable->first_process);
	}
	if (returnable)
		term->last_return = returnable->first_process->status;
	restore_fds(term);
	if (term->flag_debug == 1)
		debug_printing(term->jobs);
	free_ast(root);
	return (returnable);
}
