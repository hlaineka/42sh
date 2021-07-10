/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:35:38 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/10 21:09:15 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <signal.h>
# include "structs_21.h"
# include "typedefs.h"
# include "execution.h"

t_job		*find_last_stopped_job(t_term *term);
t_job		*find_pgid_job(t_term *term, pid_t pgid);
int			get_job_status(t_job *job);
const char	*get_stop_signal_str(t_job *job);
int			is_job_completed(t_job *job);
int			is_job_stopped(t_job *job);
int			start_stopped_job(t_job *job, t_term *term);

t_job		*get_current_job(t_term *term);
t_job		*get_current_job_builtin(t_term *term);
#endif
