/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:02:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/17 17:41:42 by hhuhtane         ###   ########.fr       */
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

# include "includes.h"
# include "structs_21.h"

void		initialize(t_input *input, t_term *term);

void		err_fatal(int error_no, char *s_str, t_term *term);
void		err_quit(int error_no, char *s_str);

/*
** TERMINAL
*/
void		enable_raw_mode(t_term *term);
void		disable_raw_mode(t_term *term);
void		print_prompt(int mode);

char		*get_input(int argc, char **argv, t_term *term, t_input *input);

int			ft_putc(int c);

/*
** CHECK WHICH KEY IT IS
*/
int			ft_is_up_key(char *str);
int			ft_is_down_key(char *str);
int			ft_is_left_key(char *str);
int			ft_is_right_key(char *str);
int			ft_is_home_key(char *str);
int			ft_is_end_key(char *str);
int			ft_is_altx_key(char *str);
int			ft_is_altc_key(char *str);
int			ft_is_altv_key(char *str);

t_clist		*ft_clstnew(void const *content, size_t content_size);
#endif
