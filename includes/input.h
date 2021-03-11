/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:02:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/11 20:18:04 by hhuhtane         ###   ########.fr       */
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

void				init_input(t_input *input);

void				err_fatal(int error_no, char *s_str, t_term *term);
void				err_quit(int error_no, char *s_str);

/*
** TERMINAL
*/
void				enable_raw_mode(t_term *term);
void				disable_raw_mode(t_term *term);

int					ft_putc(int c);

#endif
