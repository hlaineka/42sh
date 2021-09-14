/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_job_and_process_state.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:45:06 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 19:52:39 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	set_job_and_process_state(t_job *j, t_process *p, int pid, int s)
{
	j->notified = 1;
	p->pid = pid;
	p->completed = 1;
	p->status = s;
	return (s);
}
