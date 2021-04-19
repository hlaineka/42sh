/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:07:56 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/17 14:37:55 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	sig_handler_exec(int signo)
{
	t_input		*input;
	t_job		*jobs;
	t_process	*proc;

	(void)signo;
	input = g_term->input;
	jobs = g_term->jobs;
	while (jobs)
	{
		proc = jobs->first_process;
		while(proc)
		{
			if (proc->pid && (!proc->completed || !proc->stopped))
				kill(proc->pid, SIGINT);
			// set proc->completed or stopped to something
			proc = proc->next;
		}
		jobs = jobs->next;
	}
	ft_printf_fd(g_term->fd_stdout, "\n");
}
