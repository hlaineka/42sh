/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:19:46 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/15 18:24:57 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"

/*
** Adds a command to the list of commands. This list is used by lexer.
*/

void	add_command(char *command, t_editor *info)
{
	t_list	*new_command;

	new_command = ft_lstnew(command, ft_strlen(command));
	ft_lstadd(&(info->command_buf), new_command);
}
