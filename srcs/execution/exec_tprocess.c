/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:51:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/23 14:42:37 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	signal_to_default(void)
{
	int		i;

	i = 1;
	while (i < 30)
	{
		signal(i, SIG_DFL);
		i++;
	}
}

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
//	if ((g_pid = fork()) == 0)
//	ft_putendl("before fork");
	signal(SIGINT, sig_handler_exec);
//	proc->pid = fork();
	if (proc->pid == 0)
	{
//		sleep(1);
//		ft_printf_fd(4, "execve:%s\n", proc->argv[0]);
		signals_to_default();

		signal(SIGINT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
		exit(execve(fpath, proc->argv, proc->envp)); // how to return to parent?
	}
	else
/*
	else
	{
		waitpid(proc->pid, &proc->status, 0);
//		ft_printf_fd(4, "WIFEXITED=%d\n", WIFEXITED(proc->status));
//		ft_printf_fd(4, "WEXITSTATUS=%d\n", WEXITSTATUS(proc->status));
//		ft_printf_fd(4, "argv[0]=%s status=%d\n", fpath, proc->status);
	}
//		wait(NULL);
*/
	signal(SIGINT, SIG_DFL);
	return (0);
//	return ((proc->status));
}
