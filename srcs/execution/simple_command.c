/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:04:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/01 15:22:30 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/*
** BASH MANUAL says:
** Simple Commands
** A simple command is the kind of command encountered most often. It’s just a
** sequence of words separated by blanks, terminated by one of the shell’s
** control operators (see Definitions). The first word generally specifies
** a command to be executed, with the rest of the words being that command’s
** arguments.
**
** The return status (see Exit Status) of a simple command is its exit status
** as provided by the POSIX 1003.1 waitpid function, or 128+n if the command
** was terminated by signal n.
*/

static int	execve_process(t_process *proc)
{
	char	command_path[1024];
	char	*path_ptr;

	path_ptr = ft_getenv("PATH", proc->envp);
	if (is_absolute_path(proc->argv[0]))
		ft_strcpy(command_path, proc->argv[0]);
	else if (!path_ptr)
		return (err_builtin(E_ENV_PATH_NOT_SET, proc->argv[0], NULL));
	else if (find_path(proc->argv[0], path_ptr, command_path) <= 0)
		return (err_builtin(E_NO_COMMAND, proc->argv[0], NULL));
	if (access(command_path, F_OK == -1))
		return (err_builtin(E_NOENT, proc->argv[0], NULL));
	if (access(command_path, X_OK) == -1)
		return (err_builtin(E_PERM, proc->argv[0], NULL));
	signals_to_default();
	exit(execve(command_path, proc->argv, proc->envp));
}

void	get_status_and_condition(t_process *proc, int status)
{
	if (WIFEXITED(status))
	{
		proc->completed = 1;
		proc->status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		proc->completed = 1;
		proc->status = WTERMSIG(status) + 128;
	}
	else if (WIFSTOPPED(status)) // should this be before signaled?
	{
		proc->stopped = 1;
		proc->status = WIFSTOPPED(status);
	}
	else
	{
		proc->stopped = 1;
		proc->status = status;
	}
}

int	simple_command(t_process *proc)
{
	pid_t	pid;
	int		status;

	if (!proc->argv || !proc->argv[0] || proc->argv[0][0] == '\0')
	{
		ft_printf("empty argv");
		return (-1); // is this needed? what error?
	}
	if (is_builtin(proc))
		return (proc->status);
	signal(SIGINT, sig_handler_exec);
	pid = fork();
	if (pid < 0)
		return (err_builtin(E_FORK, proc->argv[0], NULL));
	if (pid == 0)
		exit(execve_process(proc));
	proc->pid = pid;
	waitpid(pid, &status, 0); // check the status with those macros?
	get_status_and_condition(proc, status);
	return (proc->status);
}
