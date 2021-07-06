/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pgid_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/06 19:59:07 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job	*find_pgid_job(t_term *term, pid_t pgid)
{
	t_job		*jobs;

	jobs = term->jobs;
	while (jobs)
	{
		if (jobs->pgid == pgid)
			return (jobs);
		jobs = jobs->next;
	}
	return (NULL);
}
