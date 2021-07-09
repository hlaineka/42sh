/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pgid_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/08 20:12:34 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job	*find_pgid_job(t_term *term, pid_t pgid)
{
	t_job		*jobs;

	jobs = term->jobs->next;
	while (jobs)
	{
		if (jobs->pgid == pgid)
			return (jobs);
		jobs = jobs->next;
	}
	return (NULL);
}
