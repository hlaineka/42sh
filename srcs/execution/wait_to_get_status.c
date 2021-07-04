/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_to_get_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:51:45 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/06/30 16:59:00 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	wait_to_get_status(t_process *proc, pid_t pid)
{
	int		status;
	pid_t	wpid;

	status = 0;
	wpid = waitpid(pid, &status, WUNTRACED);
	if (wpid == -1)
		exit(EXIT_FAILURE);		//todo error message
	while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (wpid == -1)
			exit(EXIT_FAILURE);	//todo error message
	}
	get_status_and_condition(proc, status);
}
