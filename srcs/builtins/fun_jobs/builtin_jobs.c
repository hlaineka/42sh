/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/08 19:30:18 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"

/*
static char	*get_job_argv(t_job *job, char *buf)
{
	t_process	*proc;
	char		**argv;

	proc = job->first_process;
	ft_bzero(buf, 1024);
	while (proc)
	{
		argv = proc->argv;
		while (argv && *argv)
		{
			ft_strcat(buf, " ");
			ft_strcat(buf, *argv);
			argv++;
		}
		proc = proc->next;
	}
	return (buf);
}

static const char	*current_job_status(t_job *job)
{
	if (is_job_stopped(job))
		return ("Stopped");
	return ("Running");
}

static void	print_job(t_job *job, int options)
{
	char	buf[1024];

	if (options == (1 << P_FLAG))
	{
		ft_printf("%d\n", job->first_process->pid);
		return ;
	}
	if (options != (1 << L_FLAG))
	{
		ft_printf("[%d]%c %s %s\n", job->pgid);
		ft_printf("%c %s %s\n", );

<current>, <state>, <command>
	}
	if (options != (1 << P_FLAG))
		ft_printf("[%d]%c ", job->pgid, '+'); // todo plus/minus what?
	if (options == (1 << L_FLAG))
		ft_printf("%s: %d", "Suspended or something else, do fn",
			job->first_process->status);
	ft_printf(" %s %s\n", current_job_status(job), get_job_argv(job, buf));
}
*/

static void	list_active_jobs(t_job *jobs, int options, char *jobspec_str)
{
	t_job	*temp;

	if (jobspec_str)
	{
		temp = find_pgid_job(g_term, ft_atoi(jobspec_str));
		print_active_job(temp, options, g_term);
//		print_job(temp, options);
		return ;
	}
	if (jobs->next)
		list_active_jobs(jobs->next, options, jobspec_str);
//	print_job(jobs, options);
	print_active_job(jobs, options, g_term);
//	ft_printf("[%d]   %s          %s\n", jobs->pgid,
//		current_job_status(jobs), get_job_argv(jobs, buf));
}

void	builtin_jobs(void *proc)
{
	t_term		*term;
	t_job		*jobs;
	t_process	*process;
	int			i;
	int			options;

	i = 0;
	options = 0;
	process = proc;
	term = g_term;
	jobs = term->jobs;
	if (!jobs->next)
		return ;
	if (process->argc == 1)
	{
		list_active_jobs(jobs->next, options, NULL);
		return ;
	}
	i = get_argv_options(process->argv, &options);
	if (options != 0
		&& (options != (1 << L_FLAG))
		&& (options != (1 << P_FLAG)))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "jobs", NULL));
	list_active_jobs(jobs->next, options, process->argv[i]);
}
