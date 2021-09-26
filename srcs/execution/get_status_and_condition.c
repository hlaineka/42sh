/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status_and_condition.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:04:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/26 18:16:51 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static const char	*g_signal_str[] = {
	"\0",
	"Hangup",
	"terminated: (SIGINT)",
	"Quit",
	"Illegal instruction",
	"Trace/BPT trap",
	"Abort trap",
	"EMT trap",
	"Floating point exception",
	"Killed",
	"Bus error",
	"Segmentation fault",
	"Bad system call",
	"Broken pipe",
	"Alarm clock",
	"Terminated",
	"Urgent condition present on socket",
	"Stop (SIGSTOP)",
	"Stop (SIGTSTP)",
	"SIGCONT",
	"SIGCHLD",
	"SIGTTIN",
	"SIGTTOU",
	"SIGIO",
	"Cputime limit exceeded",
	"SIGXFSZ",
	"Virtual timer expired",
	"Profiling timer expired",
	"SIGWINCH",
	"SIGINFO",
	"User defined signal 1",
	"User defined signal 2",
	"\0"
};

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
		if (WTERMSIG(status) < 16 || WTERMSIG(status) > 24)
			ft_printf("%s: %d",
				g_signal_str[WTERMSIG(status)], WTERMSIG(status));
		ft_putchar('\n');
	}
	else if (WIFSTOPPED(status))
	{
		proc->stopped = 1;
		proc->status = WSTOPSIG(status) + 128;
		ft_putchar('\n');
	}
}
