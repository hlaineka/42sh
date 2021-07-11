/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_active_job.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:23:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 21:23:34 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"

static void	print_job_current(t_job *job, t_term *term, int opt)
{
	t_job	*current;

	if (!term->jobs)
		return ;
	if (opt & (1 << J_FLAG))
		current = term->jobs->next->next;
	else
		current = term->jobs->next;
	if (!current)
		return ;
	if (job == current)
		ft_putchar('+');
	else if (job == current->next)
		ft_putchar('-');
	else
		ft_putchar(' ');
	ft_putchar('\t');
}

static void	print_job_state(t_job *job)
{
	int		status;

	status = 0;
	if (is_job_completed(job))
	{
		status = get_job_status(job);
		if (status == 0)
			ft_printf("Done");
		else
			ft_printf("Done(%d)", status);
	}
	else if (is_job_stopped(job))
		ft_printf("Stopped (%s)", get_stop_signal_str(job));
	else
		ft_printf("Running");
	ft_putchar(' ');
}

static void	print_process(t_process *proc, t_job *job)
{
	if (proc->next)
	{
		print_process(proc->next, job);
		ft_putchar('\t');
	}
	ft_printf("%d ", proc->pid);
	print_job_state(job);
	ft_putchar('\t');
	ft_printf("%s ", job->command);
	ft_putchar('\n');

}

int	print_active_job(t_job *job, int options, t_term *term)
{
	t_process	*proc;

	proc = job->first_process;
	if (options & (1 << P_FLAG))
		return (ft_printf("%d\n", job->pgid));
	ft_printf("[%d]", job->job_id);
	print_job_current(job, term, options);
	if (!(options & (1 << L_FLAG)))
	{
		print_job_state(job);
		ft_putchar('\t');
		ft_printf("%s\n", job->command);
		return (0);
	}
	print_process(proc, job);
	return (0);
/*
	while(proc)
	{
		if (proc != job->first_process)
			ft_putchar('\t');
		ft_printf("%d ", proc->pid);
		print_job_state(job);
		ft_putchar('\t');
		ft_printf("%s ", job->command);
		ft_putchar('\n');
		proc = proc->next;
	}
	return (0);
*/
}
