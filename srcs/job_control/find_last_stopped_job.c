/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last_stopped_job.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/04 21:48:23 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job	*find_last_stopped_job(t_term *term)
{
	t_job		*jobs;
	t_job		*last_stopped_job;
	t_process	*proc;

	last_stopped_job = NULL;
	jobs = term->jobs;
	while (jobs)
	{
		proc = jobs->first_process;
		while (proc)
		{
			if (proc->stopped)
				last_stopped_job = jobs;
			proc = proc->next;
		}
		jobs = jobs->next;
	}
	return (last_stopped_job);
}
