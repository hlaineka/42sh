/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 21:21:07 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/08 19:23:16 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int	get_job_status(t_job *job)
{
	t_process	*proc;

	if (!job || !job->first_process)
		return (-1);
	proc = job->first_process;
	while (proc->next)
		proc = proc->next;
	return (proc->status);
}

static const char	*get_signal_str(int signal)
{
	if (signal == 17)
		return ("SIGSTOP");
	if (signal == 18)
		return ("SIGTSTP");
	if (signal == 21)
		return ("SIGTTIN");
	if (signal == 22)
		return ("SIGTTOU");
	else
		return ("");
}

const char	*get_stop_signal_str(t_job *job)
{
	t_process	*proc;

	if (!job || !job->first_process)
		return ("");
	proc = job->first_process;
	while (proc)
	{
		if (proc->stopped && proc->status > 129)
			return (get_signal_str(proc->status - 128));
		proc = proc->next;
	}
	return ("");
}
