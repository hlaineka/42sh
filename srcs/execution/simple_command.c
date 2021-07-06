/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:04:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/06 16:57:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_signal.h"

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
	else if (WIFSTOPPED(status))
	{
		proc->stopped = 1;
		proc->status = WIFSTOPPED(status);
		ft_putchar('\n');
	}
	else
	{
		proc->stopped = 1;
		proc->status = status;
	}
}

int	simple_command(t_process *proc, t_job *job, t_term *term)
{
	pid_t	pid;
//	int		status;

	if (!proc->argv || !proc->argv[0] || proc->argv[0][0] == '\0')
		return (-1);
	if (!proc->envp)
		proc->envp = term->envp;
	if (is_builtin(proc))
		return (proc->status);
	set_signal_execution();
	pid = fork();
	if (pid < 0)
		return (err_builtin(E_FORK, proc->argv[0], NULL));
	if (pid == 0)
	{
		setpgid(0, 0);
		exit(execve_process(proc));
	}
	setpgid(pid, 0);
	job->pgid = get_next_job_pgid(term->jobs);
//	job->pgid = pid;
	tcsetpgrp(term->fd_stderr, pid);	// if not bg
	proc->pid = pid;
//	signal(SIGCHLD, SIG_DFL);	// put to set_signal_execution();
	wait_to_get_status(proc);
	tcsetpgrp(term->fd_stderr, getpgrp());	// if not bg
//	waitpid(pid, &status, WUNTRACED);
//	get_status_and_condition(proc, status);
	return (proc->status);
}

int	simple_command_pipe(t_process *proc, t_term *term)
{
	signals_to_default();
	if (!proc->argv || !proc->argv[0] || proc->argv[0][0] == '\0')
		exit(1);
	if (!proc->envp)
		proc->envp = term->envp;
	if (is_builtin(proc))
		exit(proc->status);
//		return (proc->status);
	exit(execve_process(proc));
	return (-1);
}
