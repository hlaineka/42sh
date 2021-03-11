/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_21.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:36:08 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/11 18:59:47 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_21_H
# define STRUCTS_21_H

typedef struct termios	t_termios;

typedef struct			s_input
{
	char				*ls;
	char				*rrs;
	int					ls_size;
	int					rrs_size;
}						t_input;

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

/*
*********** TERMCAPS STRINGS **************
** ft_select have these: cl, cm, cd, li, co, so, se, mr, me, us, ue vi, ve
**						ti, te
** use ioctl instead of 'li' and 'co'
***** INIT STUFF
** `ti'		String of commands to put the terminal into whatever special modes
**			are needed or appropriate for programs that move the cursor
**			nonsequentially around the screen. Programs that use termcap to do
**			full-screen display should output this string when they start up.
**
** `te'		String of commands to undo what is done by the `ti' string.
**			Programs that output the `ti' string on entry should output this
**			string when they exit.
**
***** CLEAR TERMINAL SCREEN
** `cl'		String of commands to clear the entire screen and position the
**			cursor at the upper left corner.
**
** `cd'		String of commands to clear the line the cursor is on, and all the
**			lines below it, down to the bottom of the screen. This command
**			string should be used only with the cursor in column zero; their
**			effect is undefined if the cursor is elsewhere.
**
** `ce'		String of commands to clear from the cursor to the end of the
**			current line.
**
***** CURSOR MOTION
** `cm'		String of commands to position the cursor at line l, column c.
**			Both parameters are origin-zero, and are defined relative to the
**			screen, not relative to display memory. All display terminals
**			except a few very obsolete ones support `cm', so it is acceptable
**			for an application program to refuse to operate on terminals
**			lacking `cm'.
*/

typedef struct			s_term
{
	char				*term_buffer;
	char				*termtype;
	char				*buffer;
	t_termios			orig_termios;
	char				*cl_string;
	char				*cm_string;
	int					height;
	int					width;
	int					fd_term_out; // ?
}						t_term;

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
