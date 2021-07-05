/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/05 19:35:41 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "job_control.h"

static char	*get_job_argv(t_job *job, char *buf)
{
	(void)job;
	ft_strcpy(buf, "TESTI 123");
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
	int		i;

	i = 1;
	while (jobs)
	{
		if (!(is_job_completed(jobs)))
			ft_printf("[%d]   %s          %s\n", i++,
				current_job_status(jobs), get_job_argv(jobs, buf));
		jobs = jobs->next;
	}
}

void	builtin_jobs(void *proc)
{
	t_term		*term;
	t_job		*jobs;
	t_process	*process;

	process = proc;
	term = g_term;
	jobs = term->jobs;
	list_active_jobs(jobs);
}
