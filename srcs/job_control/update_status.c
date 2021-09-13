/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 09:05:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/12 20:35:15 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "structs_21.h"
#include "typedefs.h"
#include "builtins.h"
#include "ft_signal.h"

static int	mark_process_status(pid_t pid, int status, t_term *term, int o)
{
	t_job		*j;
	t_process	*proc;

	j = term->jobs->next;
	if (pid <= 0)
		return (1);
	while (j)
	{
		proc = j->first_process;
		while (proc)
		{
			if (pid == proc->pid)
			{
				get_status_and_condition(proc, status);
				if (o == 2 && WIFSIGNALED(status))
					print_active_job(j, 0, term);
				return (0);
			}
			proc = proc->next;
		}
		j = j->next;
	}
	ft_printf("miksi pid=%d status=%d\n", pid, status);
	return (0);		// todo error or 1?
}

void	update_status_jobs(t_term *term)
{
	int			status;
	pid_t		pid;

	set_signal_execution();
	pid = waitpid (-1, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status, term, 1))
	{
		pid = waitpid (-1, &status, WUNTRACED|WNOHANG);
	}
}

void	update_status(t_term *term)
{
//	t_job		*jobs;
//	t_process	*proc;
	int			status;
	pid_t		pid;

/*
	jobs = term->jobs->next;
	while(jobs)
	{
		proc = jobs->first_process;
		while (proc)
		{
			if (!proc->completed && !proc->stopped)
			{
				pid = waitpid (proc->pid, &status, WUNTRACED|WNOHANG);
				mark_process_status(term->jobs->next, pid, status, term);
			}
			proc = proc->next;
		}
		jobs = jobs->next;
	}
*/
	set_signal_execution();
	pid = waitpid (-1, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status, term, 0))
	{
		pid = waitpid (-1, &status, WUNTRACED|WNOHANG);
	}
}
