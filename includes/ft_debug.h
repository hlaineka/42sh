/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:55:03 by helvi             #+#    #+#             */
/*   Updated: 2021/03/16 12:50:52 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEGUG_H
# define FT_DEBUG_H

//# include <termios.h>
//# include <sys/ioctl.h>
//# include <sys/types.h>
//# include <sys/wait.h>
//# include <sys/stat.h>
# include "libft.h"
# include <stdbool.h>
# define UP 279165
# define LEFT 279168
# define RIGHT 279167
# define DOWN 279166
# define ESC 27

int	g_errnbr;

typedef struct			s_editor
{
	struct termios		*original_termios;
	struct termios		*termios;
	t_list				*command_buf;
	t_list				*print_buf;
	int					screenrows;
	int					screencols;
	int					cursorrow;
	int					cursorcol;
	int					cursorshift;
	char				**envp_pointer;
	bool				quote_open;
	bool				singlequote_open;
}						t_editor;

typedef struct			s_command
{
	char				**command_argv;
	struct s_command	*next_command;
}						t_command;

/*
** rawmode.c
*/

void					enable_rawmode(t_editor *info);
int						h_disable_rawmode();
void					check_window_size(t_editor *info);
int						save_cursor_position(t_editor *info);

/*
** screen_printing.c
*/

void					helvi_clear_screen();
int						print_info();
void					reprint_row(char *command, int lenght, int cursorshift);

/*
** text_editing.c
*/

char					*delete_last(char *command, t_editor *info);
int						handle_esc(char c, char *command, char **temp);
char					*handle_printable(char *command, char c,
						t_editor *info);
char					*delete_middle(char *command, t_editor *info);
char					*add_char_to_middle(char *command, t_editor *info,
						char i);

/*
** arrows.c
*/

t_list					*arrow_up(char **command, t_list *command_list);
void					arrow_left(t_editor *info, char *command);
void					arrow_right(t_editor *info);

/*
** input.c
*/

char					*input(t_editor *info);

/*
** command_list.c
*/

void					add_command(char *command, t_editor *info);


#endif
