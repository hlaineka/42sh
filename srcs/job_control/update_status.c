/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 09:05:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 13:44:20 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "structs_21.h"
#include "typedefs.h"
#include "builtins.h"
#include "ft_signal.h"

static int	mark_process_status(t_job *j, pid_t pid, int status, t_term *term)
{
	t_process	*proc;

	if (pid <= 0)
		return (1);
	while (j)
	{
//		ft_printf("%s pid=%d status=%d\n", __FUNCTION__, pid, status);
		proc = j->first_process;
		while (proc)
		{
			if (pid == proc->pid)
			{
				get_status_and_condition(proc, status);
				if (WIFSIGNALED(status))
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
	while (!mark_process_status(term->jobs->next, pid, status, term))
	{
		pid = waitpid (-1, &status, WUNTRACED|WNOHANG);
	}

}
