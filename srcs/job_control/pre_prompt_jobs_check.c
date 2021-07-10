/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_prompt_jobs_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 17:03:39 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/10 18:44:27 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "job_control.h"
#include "execution.h"
#include "builtins.h"

void	pre_prompt_jobs_check(t_term *term)
{
	t_job	*jobs;

	if (!term || !term->jobs || !term->jobs->next)
		return ;
	jobs = term->jobs->next;
	while (jobs)
	{
		if (!is_job_stopped(jobs) && !is_job_completed(jobs))
		{
			wait_job_and_get_status(jobs, term);
			if (!is_job_stopped(jobs) || !is_job_completed(jobs))
				print_active_job(jobs, 0, term);
		}
		jobs = jobs->next;
	}
	free_jobs(term);
}
