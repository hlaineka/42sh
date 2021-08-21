/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:37:52 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/14 08:49:04 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "includes.h"
# include "structs_21.h"
# include "input.h"

int			get_last_history_index(char **history);
int			add_cmd_to_history(char *cmd, char **history);

/*
** BANG FUNCTIONS:
*/

const char	*bang_selector(char *bang_param, t_term *term);
const char	*bang_bang_fun(t_term *term);
const char	*bang_number_fun(char *number_str, t_term *term);
const char	*bang_minus_number_fun(char *number_str, t_term *term);
const char	*bang_word_fun(char *word, t_term *term);

/*
** HISTORY STUFF:
*/

void		history_search_start(t_input *input, t_term *term);
int			incremental_history_search(char *rc, t_input *input, t_term *term);

#endif
