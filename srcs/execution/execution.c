/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:28:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/07 15:55:56 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	execute_jobs(t_job *jobs, char **envp)
{
	t_process	*current;

	while (jobs)
	{
		// change original fds?
		current = jobs->first_process;
		while (current)
		{
			current->envp = envp;
			current->argc = ft_strarrlen(current->argv);
			if (!is_builtin(current))
				ft_putendl("exec function stuff here");
			current = current->next;
		}
		// do we need to return fds to normal?
		jobs = jobs->next;
	}
}
