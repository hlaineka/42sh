/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:37:52 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/17 11:44:53 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "includes.h"
# include "structs_21.h"
# include "input.h"

void		disable_raw_mode_continue(t_term *term);
void		disable_raw_mode(t_term *term);
int			disable_rawmode(void);
void		get_termios_modes(t_term *term);
void		enable_raw_mode(t_term *term);
void		initialize(t_input *input, t_term *term, char **envp, char **argv);
void		init_input(t_input *input);

#endif