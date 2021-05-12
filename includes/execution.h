/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:35:38 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/12 10:42:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include <stdbool.h>

t_job		*execute(t_node *root, t_term *term);
void		execute_jobs(t_job *jobs, t_term *term);

int			fork_and_chain_pipes(int *lpipe, int *rpipe);

int			simple_command(t_process *proc);

void		get_status_and_condition(t_process *proc, int status);

/*
** execution/job_creation/job_creation.c
*/

t_job		*job_creation(t_node *root, t_term *term);

/*
** execution/job_creation/job_functions.c
*/

void		free_jobs(t_term *term);
t_job		*init_job(t_term *term);
t_process	*init_process(t_term *term);
void		free_job(t_job *job_to_free);
void		restore_fds(t_term *term);

/*
** execution/job_creation/job_functions2.c
*/

void		update_fds(t_term *term);
void		get_right(t_node *current, t_term *term);

/*
** execution/job_creation/pipe_functions.c
*/

t_job		*pipe_start(t_job *job, t_term *term, t_node *current);
t_job		*pipe_middle(t_job *job, t_term *term, t_node *current);
t_job		*pipe_end(t_job *job, t_term *term, t_node *current);

/*
** execution/job_creation/tree_traversal.c
*/

t_job		*tree_traversal(t_job *job, t_node *current, t_term *term);

/*
** execution/job_creation/redirection_functions.c
*/
t_job		*get_left_job(t_job *job, t_node *current, t_term *term);
t_job		*get_right_job(t_job *job, t_node *current, t_term *term);
char		*get_filename(t_node *current);
int			get_fd(t_node *current, int default_fd);
int			close_fd(int old_fd);

int			check_fd(int fd, int errormessage);

/*
** execution/job_creation: operation function pointers, all in their own files
** named like function() -> function.c
*/

t_job		*token_null(t_job *job, t_term *term, t_node *current);
t_job		*token_semi(t_job *job, t_term *term, t_node *current);
t_job		*token_pipe(t_job *job, t_term *term, t_node *current);
t_job		*token_great(t_job *job, t_term *term, t_node *current);
t_job		*token_less(t_job *job, t_term *term, t_node *current);
t_job		*token_dgreat(t_job *job, t_term *term, t_node *current);
t_job		*token_greatand(t_job *job, t_term *term, t_node *current);
t_job		*token_lessand(t_job *job, t_term *term, t_node *current);
t_job		*token_dless(t_job *job, t_term *term, t_node *current);
t_job		*token_and_if(t_job *job, t_term *term, t_node *current);
t_job		*token_or_if(t_job *job, t_term *term, t_node *current);

void		get_right(t_node *current, t_term *term);
void		update_fds(t_term *term);

#endif
