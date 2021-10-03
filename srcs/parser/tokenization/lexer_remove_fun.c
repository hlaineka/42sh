/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_remove_fun.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:26:22 by hlaineka          #+#    #+#             */
/*   Updated: 2021/10/03 20:32:14 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "execution.h"

static char	*handle_backslash_remove(char *str, int i)
{
	char	*new;
	int		w;
	int		len;

	len = ft_strlen(str) + 1;
	new = ft_strnew(len + 1);
	w = 0;
	while (w < i)
	{
		new[w] = str[w];
		w++;
	}
	new[w++] = 39;
	i++;
	new[w++] = str[i++];
	new[w++] = 39;
	while (w < len)
		new[w++] = str[i++];
	new[w] = '\0';
	ft_free(str);
	return (new);
}

/*
** ascii 92 == \
*/

char	*remove_backslash(char *str)
{
	int		i;
	bool	single_quoted;
	bool	double_quoted;

	i = 0;
	single_quoted = FALSE;
	double_quoted = FALSE;
	while (str[i])
	{
		if (str[i] == 34)
			double_quoted = !double_quoted;
		if (str[i] == 39)
			single_quoted = !single_quoted;
		if (!single_quoted && !double_quoted && str[i] == 92
			&& str[i + 1] == '\n')
			str = ft_strcut(str, i, i + 2);
		else if (!single_quoted && !double_quoted && str[i] == 92
			&& str[i + 1] != 39)
		{
			str = handle_backslash_remove(str, i);
			i = -1;
		}
		i++;
	}
	return (str);
}

t_token	*delete_until_token(t_token *tkn)
{
	t_token	*returnable;

	returnable = NULL;
	if (tkn)
		returnable = tkn->next;
	if (tkn->value)
		ft_memdel((void **)&tkn->value);
	if (tkn->quotes)
		ft_memdel((void **)&tkn->quotes);
	if (tkn->full_command)
		ft_memdel((void **)&tkn->full_command);
	ft_memdel((void **)&tkn);
	return (returnable);
}

t_token	*delete_until(t_token *temp, t_term *term)
{
	t_token	*next;

	while (temp && temp->maintoken != tkn_semi && temp->maintoken != tkn_and
		&& temp->maintoken != tkn_or_if)
	{
		if (temp->maintoken == tkn_and_if
			&& term->jobs->next->first_process->status == 0)
			break ;
		next = temp->next;
		delete_token(temp);
		temp = next;
	}
	if (temp)
	{
		next = temp->next;
		delete_token(temp);
		temp = next;
		if (temp)
			temp->prev = NULL;
	}
	return (temp);
}
