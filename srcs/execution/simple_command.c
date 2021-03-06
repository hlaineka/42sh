/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:04:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/03 22:59:21 by hhuhtane         ###   ########.fr       */
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

static int	get_abs_path_to_cmd(char *cmd, char **envp, t_hash *ht, char *buf)
{
	char	*path_ptr;

	path_ptr = ft_getenv("PATH", envp);
	if (!path_ptr)
		path_ptr = ft_getenv("PATH", g_term->intern_variables->intern);
	if (is_absolute_path(cmd))
		ft_strcpy(buf, cmd);
	else if (is_in_hash_table(cmd, ht))
		create_full_cmd(cmd, ht, buf);
	else if (!path_ptr)
	{
		return (err_builtin(E_ENV_PATH_NOT_SET, cmd, NULL));
	}
	else if (find_path(cmd, path_ptr, buf) <= 0)
		return (err_builtin(E_NO_COMMAND, cmd, NULL));
	add_cmd_to_hash_table(cmd, envp, ht, cmd);
	increase_hash_table_hits(cmd, ht);
	return (0);
}

static int	execve_process(char *cmd_abs, t_process *proc, t_term *term)
{
	char	*cmd;
	char	**envp;

	if (proc->envp)
		envp = proc->envp;
	else
		envp = term->envp;
	cmd = proc->argv[0];
	if (access(cmd_abs, F_OK == -1))
		return (err_builtin(E_NOENT, cmd, NULL));
	if (access(cmd_abs, X_OK) == -1)
		return (err_builtin(E_PERM, cmd, NULL));
	signals_to_default();
	exit(execve(cmd_abs, proc->argv, envp));
}

static int	parent_shell_return(t_process *proc, t_job *job, t_term *term)
{
	pid_t	pid;

	pid = proc->pid;
	set_signal_execution();
	setpgid(pid, 0);
	job->job_id = get_next_job_pgid(term->jobs->next);
	job->pgid = pid;
	if (!job->bg)
		tcsetpgrp(term->fd_stderr, pid);
	proc->pid = pid;
	wait_to_get_status(proc, job->bg);
	if (!job->bg && job->first_process->stopped == 0)
		job->notified = 1;
	tcsetpgrp(term->fd_stderr, getpgrp());
	return (proc->status);
}

int	simple_command(t_process *proc, t_job *job, t_term *term)
{
	pid_t	pid;
	char	cmd_abs[1024];

	if (!proc->argv || !proc->argv[0] || proc->argv[0][0] == '\0')
		return (set_job_and_process_state(job, proc, -1, 1));
	if (is_builtin(proc))
		return (set_job_and_process_state(job, proc, -1, proc->status));
	if (get_abs_path_to_cmd(proc->argv[0],
			term->envp, term->hash_table, cmd_abs) != 0)
		return (set_job_and_process_state(job, proc, -1, 1));
	if (job->bg)
		exit(execve_process(cmd_abs, proc, term));
	pid = fork();
	if (pid < 0)
		return (err_builtin(E_FORK, proc->argv[0], NULL));
	if (pid == 0)
	{
		setpgid(0, 0);
		exit(execve_process(cmd_abs, proc, term));
	}
	proc->pid = pid;
	return (parent_shell_return(proc, job, term));
}

int	simple_command_pipe(t_process *proc, t_term *term)
{
	char	cmd_abs[1024];

	signals_to_default();
	if (!proc->argv || !proc->argv[0] || proc->argv[0][0] == '\0')
		exit(1);
	if (is_builtin(proc))
		exit(proc->status);
	if (get_abs_path_to_cmd(proc->argv[0], term->envp,
			term->hash_table, cmd_abs) != 0)
		exit (1);
	exit(execve_process(cmd_abs, proc, term));
	return (-1);
}
