/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:37:52 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/12 11:30:15 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "includes.h"
# include "structs_21.h"
# include "input.h"

int		get_last_history_index(char **history);
int		add_cmd_to_history(char *cmd, char **history);

#endif
