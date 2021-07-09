/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 21:59:59 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/08 22:05:00 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "typedefs.h"
#include "execution.h"

pid_t	get_last_process_pid(t_job *job)
{
	t_process	*proc;

	proc = job->first_process;
	while (proc->next)
		proc = proc->next;
	return (proc->pid);
}
