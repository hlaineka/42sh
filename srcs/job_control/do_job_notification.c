/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_job_notification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 08:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 09:42:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "structs_21.h"
#include "typedefs.h"
#include "builtins.h"

void	do_job_notification(t_job *j_prev, t_term *term)
{
	t_job	*job;

	update_status(term);
	job = j_prev->next;
	while (job)
	{
		if (is_job_completed(job))
		{
			print_active_job(job, 0, term);
			j_prev->next = job->next;
			free_job(job);
		}
		else if (is_job_stopped(job) && !job->notified)
		{
			print_active_job(job, 0, term);
			job->notified = 1;
			j_prev = j_prev->next;
		}
		else
			j_prev = j_prev->next;
		job = j_prev->next;
	}
}
