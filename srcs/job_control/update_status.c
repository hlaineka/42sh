/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 09:05:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 09:43:10 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "structs_21.h"
#include "typedefs.h"
#include "builtins.h"

static int	mark_process_status(t_job *j, pid_t pid, int status, t_term *term)
{
	t_process	*proc;

	if (pid <= 0)
		return (pid);
	while (j)
	{
		proc = j->first_process;
		while (proc)
		{
			if (pid == proc->pid)
			{
				get_status_and_condition(proc, status);
				if (WIFSIGNALED(status))
					print_active_job(j, 0, term);
				return (1);
			}
			proc = proc->next;
		}
		j = j->next;
	}
	return (0);		// todo error or 1?
}

void	update_status(t_term *term)
{
	int		status;
	pid_t	pid;

	pid = waitpid (-1, &status, WUNTRACED|WNOHANG);
	while (mark_process_status(term->jobs->next, pid, status, term) > 0)
	{
		pid = waitpid (-1, &status, WUNTRACED|WNOHANG);
	}
}
