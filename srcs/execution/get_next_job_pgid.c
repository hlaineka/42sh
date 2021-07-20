/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_job_pgid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:49:36 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/10 12:07:36 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"

int	get_next_job_pgid(t_job *jobs)
{
	int		largest;

	largest = 0;
	if (!jobs)
		return (1);
	while (jobs)
	{
		if (largest < jobs->job_id)
			largest = jobs->job_id;
		jobs = jobs->next;
	}
	largest++;
	return (largest);
}
