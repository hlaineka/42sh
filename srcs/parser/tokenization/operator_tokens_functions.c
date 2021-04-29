/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:58:07 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 09:59:56 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Functions to add subtokens to redirection operators.
*/

int	handle_tkn_io_number(t_token *current)
{
	int		i;
	t_token	*new_subtoken;

	i = 0;
	new_subtoken = NULL;
	while (current->value[i] && ft_isdigit(current->value[i]))
		i++;
	if (!ft_strchr(OPCHARS, current->value[i]))
		return (-1);
	if (i > 0)
	{
		new_subtoken = init_token();
		new_subtoken->maintoken = tkn_io_number;
		new_subtoken->value = ft_strcut(current->value, 0, i);
		add_subtoken(current, new_subtoken);
	}
	return (0);
}

int	add_filename_tkn(t_token *current)
{
	if (!current->next || current->next->maintoken != tkn_word)
		return (-1);
	add_subtoken(current, current->next);
	return (0);
}
