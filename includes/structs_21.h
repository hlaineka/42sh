/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_21.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:36:08 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/08 17:59:35 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_21_H
# define STRUCTS_21_H

typedef struct termios	t_termios;

typedef struct			s_process
{
	struct s_process	*next;       /* next process in pipeline */
	char				**argv;      /* for exec */
	pid_t				pid;         /* process ID */
	char				completed;   /* true if process has completed */
	char				stopped;     /* true if process has stopped */
	int					status;      /* reported status value */
}						t_process;

/* A job is a pipeline of processes.  */
typedef struct			s_job
{
	struct s_job		*next;          /* next active job, if not t_list */
	char				*command;       /* command line, used for messages */
	t_process			*first_process; /* list of processes in this job */
	pid_t				pgid;           /* process group ID */
	char				notified;       /* true if user told about stopped job */
	t_termios			tmodes;         /* saved terminal modes */
	t_termios			orig_termios;   /* is this the same as abowe? */
	int					fd_stdin;
	int					fd_stdout;
	int					fd_stderr;
}						t_job;

typedef struct			s_termcaps
{
	char				*term_buffer;
	char				*termtype;
	char				*buffer;
	char				*cl_string;
	char				*cm_string;
	int					height;
	int					width;
}						t_termcaps;

typedef struct			s_itty
{
	char				*ls;
	char				*rrs;
	int					ls_i;
	int					rrs_i;
	//current location before prompt print
	//current location after prompt print
	//current location after ls print
}						t_itty;

#endif
