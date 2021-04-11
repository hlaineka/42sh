/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:51:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/11 12:45:32 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	exec_tprocess(t_process *proc)
{
	char		fpath[1024];
	char		*path_ptr;

	path_ptr = ft_getenv("PATH", proc->envp);
	if (is_absolute_path(proc->argv[0]))
		ft_strcpy(fpath, proc->argv[0]);
	else if (!path_ptr)
		return (err_builtin(E_ENV_PATH_NOT_SET, proc->argv[0], NULL));
	else if (find_path(proc->argv[0], path_ptr, fpath) <= 0)
		return (err_builtin(E_NO_COMMAND, proc->argv[0], NULL));
	if (access(fpath, F_OK) == -1)
		return (err_builtin(E_NOENT, proc->argv[0], NULL));
	if (access(fpath, X_OK) == -1)
		return (err_builtin(E_PERM, proc->argv[0], NULL));
	if ((g_pid = fork()) == 0)
	{
		exit(execve(fpath, proc->argv, proc->envp)); // how to return to parent?
	}
	else
		wait(NULL);
	return ((g_pid = 0));
}
