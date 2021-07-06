/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/06 17:16:45 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "job_control.h"

static char	*get_job_argv(t_job *job, char *buf)
{
	t_process	*proc;
	char		**argv;

	proc = job->first_process;
	ft_bzero(buf, 1024);
	while (proc)
	{
		argv = proc->argv;
		while (argv && *argv)
		{
			ft_strcat(buf, " ");
			ft_strcat(buf, *argv);
			argv++;
		}
		proc = proc->next;
	}
	return (buf);
}

static const char	*current_job_status(t_job *job)
{
	if (is_job_stopped(job))
		return ("Stopped");
	return ("Running");
}

void	list_active_jobs(t_job *jobs)
{
	char	buf[1024];

	if (jobs->next)
		list_active_jobs(jobs->next);
	ft_printf("[%d]   %s          %s\n", jobs->pgid,
		current_job_status(jobs), get_job_argv(jobs, buf));
}

void	builtin_jobs(void *proc)
{
	t_term		*term;
	t_job		*jobs;
	t_process	*process;

	process = proc;
	term = g_term;
	jobs = term->jobs;
	if (!jobs->next)
		return ;
	list_active_jobs(jobs->next);
}
