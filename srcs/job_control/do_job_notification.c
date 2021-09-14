/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_job_notification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 08:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/13 13:58:35 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include "job_control.h"
#include "structs_21.h"
#include "typedefs.h"
#include "builtins.h"
#include "input.h"

void	do_job_notification(t_job *j_prev, t_term *term)
{
	t_job	*job;

	update_status(term);
	job = j_prev->next;
	tputs(term->cd_string, 1, ft_putc);
	while (job)
	{
		if (is_job_completed(job))
		{
			if (!job->notified)
				print_active_job(job, 0, term);
			j_prev->next = job->next;
			free_job(job);
			job = NULL;
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
