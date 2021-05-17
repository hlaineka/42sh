/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:02:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/17 11:44:49 by hlaineka         ###   ########.fr       */
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
# define PROMPT_HEREDOC 127

# include "includes.h"
# include "structs_21.h"

char		*get_input(int argc, char **argv, t_term *term, t_input *input);
char		*get_input_heredoc(char *eof, t_input *input, t_term *term);

char		*read_input_tty(int prompt_mode, t_input *input, t_term *term);
int			copy_envp(char **envp, t_term *term);

void		err_fatal(int error_no, char *s_str, t_term *term);
void		err_quit(int error_no, char *s_str);
int			err_return(int error_no, char *s_str);

void		init_input_tty(t_input *input, int prompt_mode);

/*
** TERMINAL
*/
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
void		paste_clipboard_to_input(t_input *input, t_term *term);
void		copy_input_to_clipboard(t_input *input, t_term *term);
void		cut_input_to_clipboard(t_input *input, t_term *term);
int			react_to_eof(t_input *input, t_term *term);

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
int			ft_is_shift_up_key(char *str);
int			ft_is_shift_down_key(char *str);
int			ft_is_shift_left_key(char *str);
int			ft_is_shift_right_key(char *str);
int			ft_is_home_key(char *str);
int			ft_is_end_key(char *str);
int			ft_is_altx_key(char *str);
int			ft_is_altc_key(char *str);
int			ft_is_altv_key(char *str);
int			ft_is_delete_key(char *str);

int			ft_is_quote_open(int quote, char *str);

t_clist		*ft_clstnew(void const *content, size_t content_size);

void		clear_rows_starting_y(int y, t_term *term);
void		clear_screen_after_prompt(t_input *input, t_term *term);

int			double_input_mem(t_input *input, t_term *term);
#endif
