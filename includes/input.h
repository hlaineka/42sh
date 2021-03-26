/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:02:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 12:26:19 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/*
** DEFINE ERROR NUMBERS
*/
# define ERR_MALLOC 1
# define ERR_READ 2
# define ERR_MESSAGE 3
# define ERR_TERMTYPE_NOT_SET 4
# define ERR_TERMCAPS_NO_ACCESS 5
# define ERR_TERMTYPE_NOT_FOUND 6

# define PROMPT_NORMAL 0
# define PROMPT_START 1
# define PROMPT_QUOTE 39
# define PROMPT_DQUOTE 34
# define PROMPT_BQUOTE 96
# define PROMPT_ESCAPECHAR 92

# include "includes.h"
# include "structs_21.h"

void		initialize(t_input *input, t_term *term);

void		err_fatal(int error_no, char *s_str, t_term *term);
void		err_quit(int error_no, char *s_str);

/*
** TERMINAL
*/
void		get_termios_modes(t_term *term);
void		enable_raw_mode(t_term *term);
void		disable_raw_mode_continue(t_term *term);
void		disable_raw_mode(t_term *term);
int			disable_rawmode(void);
int			print_prompt(int mode);

int			move_cursor_up(int *row, int *col, t_term *term);
int			move_cursor_down(int *row, int *col, t_term *term);
int			move_cursor_right(int *row, int *col, t_term *term);
int			move_cursor_left(int *row, int *col, t_term *term);
void		move_prev_word(t_input *input, t_term *term);
void		move_next_word(t_input *input, t_term *term);

void		history_up(t_input *input, t_term *term);
void		history_down(t_input *input, t_term *term);
int			home_keypress(t_input *input, t_term *term);
int			end_keypress(t_input *input, t_term *term);
void		alt_up_keypress(t_input *input, t_term *term);
void		alt_down_keypress(t_input *input, t_term *term);
void		left_keypress(t_input *input, t_term *term);
void		right_keypress(t_input *input, t_term *term);
void		backspace_keypress(t_input *input, t_term *term);
void		delete_keypress(t_input *input, t_term *term);

char		*get_input(int argc, char **argv, t_term *term, t_input *input);
int			get_pos(int *y, int *x);

void		move_char_from_s1_to_s2(char *s1, char *s2, int s2_limit);
void		move_nchars_from_s1_to_s2(char *s1, char *s2, int limit, int n);
t_clist		*command_to_history(t_input *input, char *str);

/*
** PRINT FUNCTIONS
*/
int			ft_putc(int c);
void		ft_putstr_input(char *str, t_input *input, t_term *term);
void		ft_putrstr_input(char *str, t_input *input, t_term *term);

/*
** CHECK WHICH KEY IT IS
*/
int			shell_keypress(char *rc, t_input *input, t_term *term);

int			ft_is_up_key(char *str);
int			ft_is_down_key(char *str);
int			ft_is_left_key(char *str);
int			ft_is_right_key(char *str);
int			ft_is_home_key(char *str);
int			ft_is_end_key(char *str);
int			ft_is_altx_key(char *str);
int			ft_is_altc_key(char *str);
int			ft_is_altv_key(char *str);
int			ft_is_delete_key(char *str);

int			ft_is_quote_open(int quote, char *str);

t_clist		*ft_clstnew(void const *content, size_t content_size);
#endif
