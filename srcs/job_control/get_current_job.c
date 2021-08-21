/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_job.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:03:19 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/10 21:06:53 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "execution.h"

t_job	*get_current_job(t_term *term)
{
	t_job	*job;

	job = term->jobs;
	if (!job)
		return (NULL);
	return (job->next);
}

t_job	*get_current_job_builtin(t_term *term)
{
	t_job	*job;

	job = term->jobs;
	if (!job)
		return (NULL);
	job = job->next;
	if (!job)
		return (NULL);
	return (job->next);

}
