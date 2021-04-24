/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:35:38 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/23 14:44:06 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include <stdbool.h>

void	execute_jobs(t_job *jobs, t_term *term);
int		exec_tprocess(t_process *proc);

int		fork_and_chain_pipes(int *lpipe, int *rpipe);

int		simple_command(t_process *proc);

#endif
