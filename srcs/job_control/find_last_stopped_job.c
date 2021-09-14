/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last_stopped_job.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 18:28:04 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job	*find_last_stopped_job(t_term *term)
{
	t_job		*jobs;
	t_process	*proc;

	jobs = term->jobs->next;
	while (jobs)
	{
		proc = jobs->first_process;
		while (proc)
		{
			if (proc->stopped)
				return (jobs);
			proc = proc->next;
		}
		jobs = jobs->next;
	}
	return (NULL);
}
