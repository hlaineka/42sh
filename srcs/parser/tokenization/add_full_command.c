/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_full_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 13:40:15 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/11 15:01:10 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "includes.h"

t_token	*add_full_command(t_token *first)
{
    t_token	*temp;
	t_token	*command_first;
    char	command[STR_LENGTH + 1];
	int		i;
	int		w;

    temp = first;
	while (temp)
	{
		i = 0;
		command_first = temp;
		ft_bzero(command, STR_LENGTH);
		while (temp && temp->next && temp->maintoken != tkn_semi
			&& temp->maintoken != tkn_and && temp->maintoken != tkn_and_if
			&& temp->maintoken != tkn_or_if && temp->maintoken != tkn_rpar
			&& temp->maintoken != tkn_rbrace)
		{
			w = 0;
			while(temp->value[w])
				command[i++] = temp->value[w++];
			command[i++] = ' ';
			temp = temp->next;
		}
		if (temp)
		{
			if (temp->maintoken != tkn_semi	&& temp->maintoken != tkn_and
			&& temp->maintoken != tkn_and_if && temp->maintoken != tkn_or_if
			&& temp->maintoken != tkn_rpar && temp->maintoken != tkn_rbrace)
			{
				w = 0;
				while(temp->value[w])
					command[i++] = temp->value[w++];
				command[i++] = '\0';
			}
			temp = temp->next;
		}
		while (command_first != temp)
		{
			command_first->full_command = ft_strdup(command);
			command_first = command_first->next;
		}
	}
    return(first);
}