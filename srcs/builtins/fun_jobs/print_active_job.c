/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_active_job.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:23:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/11 17:32:16 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"

void	print_job_current(t_job *job, t_term *term)
{
	t_job	*current;

	if (!term->jobs)
		return ;
	current = term->jobs->next->next;
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

void	print_job_state(t_job *job)
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

int	print_active_job(t_job *job, int options, t_term *term)
{
	t_process	*proc;

	proc = job->first_process;
	if (options == (1 << P_FLAG))
		return (ft_printf("%d\n", job->pgid));
	ft_printf("[%d]", job->job_id);
	print_job_current(job, term);
	if (options != (1 << L_FLAG))
	{
		print_job_state(job);
		ft_putchar('\t');
		ft_printf("%s\n", job->command);
		return (0);
	}
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
}
