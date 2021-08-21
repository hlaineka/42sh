/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_job_completed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:34:35 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 10:57:25 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int	is_job_completed(t_job *job)
{
	t_process	*proc;

	proc = job->first_process;
	while (proc)
	{
		if (!proc->completed)
			return (0);
		proc = proc->next;
	}
	return (1);
}
