/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:35:38 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/03 13:16:25 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <signal.h>
# include "structs_21.h"
# include "typedefs.h"
# include "execution.h"

t_job		*find_last_stopped_job(t_term *term);
int			is_job_completed(t_job *job);
int			is_job_stopped(t_job *job);
int			start_stopped_job(t_job *job);

#endif
