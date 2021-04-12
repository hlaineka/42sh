/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_21.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:36:08 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/12 14:43:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_21_H
# define STRUCTS_21_H

# include <termios.h>
# include "libft_shorthand.h"
# include "libft.h"

# define KEY_ESC 27

typedef struct termios	t_termios;
typedef struct stat		t_stat;

typedef struct s_clist
{
	void				*content;
	size_t				content_size;
	struct s_clist		*prev;
	struct s_clist		*next;
}						t_clist;

typedef struct s_input
{
	t_clist				*hist_cur;
	t_clist				*history;
	t_clist				*last_comm;
	char				*ls;
	char				*rrs;
	char				*clipboard;
	size_t				ls_size;
	size_t				rrs_size;
	size_t				clipboard_size;
	size_t				prompt_length;
	int					start_row;
	int					start_col;
	int					prompt_row; //limit y
	int					prompt_col; //limit x
	int					cursor_row;
	int					cursor_col;
}						t_input;

typedef struct s_process
{
	struct s_process	*next;       /* next process in pipeline */
	int					argc;
	char				**argv;      /* for exec */
	char				**envp;
	pid_t				pid;         /* process ID */
	char				completed;   /* true if process has completed */
	char				stopped;     /* true if process has stopped */
	int					status;      /* reported status value */
}						t_process;

/* A job is a pipeline of processes.  */
typedef struct s_job
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
** `dc'		String of commands to delete one character position at the cursor.
**			If `dc' is not present, the terminal cannot delete characters.
**
***** CURSOR MOTION
** `cm'		String of commands to position the cursor at line l, column c.
**			Both parameters are origin-zero, and are defined relative to the
**			screen, not relative to display memory. All display terminals
**			except a few very obsolete ones support `cm', so it is acceptable
**			for an application program to refuse to operate on terminals
**			lacking `cm'.
**
** `le'		String of commands to move the cursor left one column. Unless the
**			`bw' flag capability is specified, the effect is undefined if the
**			cursor is at the left margin; do not use this command there. If
**			`bw' is present, this command may be used at the left margin, and
**			it wraps the cursor to the last column of the preceding line.
**
** `nd'		String of commands to move the cursor right one column. The effect
**			is undefined if the cursor is at the right margin; do not use this
**			command there, not even if `am' is present.
**
** `sc'		String of commands to make the terminal save the current cursor
**			position. Only the last saved position can be used. If this
**			capability is present, `rc' should be provided also. Most
**			terminals have neither.
**
** `rc'		String of commands to make the terminal restore the last saved
**			cursor position. If this capability is present, `sc' should be
**			provided also. Most terminals have neither.
*/

typedef struct s_term
{
	char				*envp[1024];
	t_input				*input;
	char				*term_buffer;
	char				*termtype;
	char				*buffer;
	t_termios			orig_termios;
	t_termios			raw;
	char				*ti_string;
	char				*te_string;
	char				*cl_string;
	char				*cd_string;
	char				*ce_string;
	char				*cm_string;
	char				*le_string;
	char				*nd_string;
	char				*sc_string;
	char				*rc_string;
	char				*dc_string;
	size_t				nrows;
	size_t				ncolumns;
	int					cursorcol;
	int					cursorrow;
	int					fd_stdin;
	int					fd_stdout;
	int					fd_stderr;
	int					flag_debug;
	int					flag_noclobber;
}						t_term;

/*
** GLOBALS
*/
t_term					*g_term;

#endif
