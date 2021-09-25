/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_full_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 13:40:15 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 12:20:23 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "includes.h"

static t_token	*copy_subtoken_command(t_token *subtoken, char *command,
	t_token *tkn)
{
	int	w;
	int	i;

	i = ft_strlen(command);
	if (subtoken->next)
	{
		w = 0;
		while (subtoken->value[w])
			command[i++] = subtoken->value[w++];
		if (!ft_is_nbrstr(subtoken->value) && !ft_strequ(subtoken->value, "-"))
			command[i++] = ' ';
		subtoken = subtoken->next;
	}
	w = 0;
	while (tkn->value[w])
		command[i++] = tkn->value[w++];
	if (!ft_strequ(subtoken->value, "-"))
		command[i++] = ' ';
	w = 0;
	while (subtoken->value[w])
		command[i++] = subtoken->value[w++];
	command[i++] = ' ';
	return (subtoken);
}

static void	copy_with_subtokens(char *command, t_token *subtoken, t_token *tkn)
{
	int		i;
	int		w;

	while (subtoken)
	{
		if (tkn->maintoken == tkn_less || tkn->maintoken == tkn_great
			|| tkn->maintoken == tkn_dless || tkn->maintoken == tkn_dgreat
			|| tkn->maintoken == tkn_lessand || tkn->maintoken == tkn_greatand
			|| tkn->maintoken == tkn_lessgreat
			|| tkn->maintoken == tkn_dlessdash || tkn->maintoken == tkn_clobber)
			subtoken = copy_subtoken_command(subtoken, command, tkn);
		else
		{
			w = 0;
			i = ft_strlen(command);
			while (tkn->value[w])
				command[i++] = tkn->value[w++];
			command[i++] = ' ';
		}
		subtoken = subtoken->next;
	}
}

void	copy_token_command(t_token *temp, char *command)
{
	int	i;
	int	w;

	w = 0;
	i = ft_strlen(command);
	while (temp->value[w])
		command[i++] = temp->value[w++];
	if (temp->maintoken != tkn_lpar && temp->maintoken != tkn_lbrace
		&& temp->maintoken != tkn_lesslpar && temp->maintoken != tkn_greatlpar
		&& temp->maintoken != tkn_dollarlpar
		&& temp->maintoken != tkn_dollarlbrace)
		command[i++] = ' ';
}

t_token	*copy_command(char *command, t_token *temp)
{
	while (temp && temp->next && temp->maintoken != tkn_semi
		&& temp->maintoken != tkn_and && temp->maintoken != tkn_and_if
		&& temp->maintoken != tkn_or_if)
	{
		if (temp->subtokens)
		{
			copy_with_subtokens(command, temp->subtokens, temp);
			temp = temp->next;
			continue ;
		}
		copy_token_command(temp, command);
		temp = temp->next;
	}
	if (temp && temp->maintoken != tkn_semi && temp->maintoken != tkn_and
		&& temp->maintoken != tkn_and_if && temp->maintoken != tkn_or_if)
		ft_strcpy(&(command[ft_strlen(command)]), temp->value);
	return (temp);
}

t_token	*add_full_command(t_token *first)
{
	t_token	*temp;
	t_token	*command_first;
	char	command[STR_LENGTH];

	temp = first;
	while (temp)
	{
		command_first = temp;
		ft_bzero(command, STR_LENGTH);
		temp = copy_command(command, temp);
		temp = temp->next;
		while (command_first != temp)
		{
			command_first->full_command = ft_strdup(command);
			command_first = command_first->next;
		}
	}
	return (first);
}
