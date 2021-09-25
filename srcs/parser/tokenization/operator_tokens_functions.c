/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:58:07 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 21:18:13 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Functions to add subtokens to redirection operators.
*/

static char	*get_io_returnable(char *str, int start, int end)
{
	int		i;
	int		w;
	char	*returnable;

	i = start;
	w = 0;
	returnable = malloc(end - start + 1);
	while (i < end)
	{
		returnable[w] = str[i];
		w++;
		i++;
	}
	returnable[w] = '\0';
	return (returnable);
}

static char	*ft_strcut_io(char *str, int start, int end)
{
	char	*returnable;
	int		i;
	int		w;
	int		len;

	returnable = get_io_returnable(str, start, end);
	len = ft_strlen(str);
	i = start;
	w = end;
	while (str[w])
	{
		str[i] = str[w];
		i++;
		w++;
	}
	while (i <= len)
		str[i++] = '\0';
	return (returnable);
}

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
		new_subtoken->value = ft_strcut_io(current->value, 0, i);
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

int	check_semi_and(t_token *first, int token)
{
	t_token	*temp2;

	temp2 = first;
	while (temp2)
	{
		if (temp2->maintoken == token)
			return (-1);
		temp2 = temp2->next;
	}
	return (0);
}
