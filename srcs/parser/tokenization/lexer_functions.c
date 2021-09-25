/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:26:22 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 19:19:32 by hlaineka         ###   ########.fr       */
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

static t_token	*run_semicolon_command(t_token **command_first, t_term *term,
	t_token *temp)
{
	t_node	*root;
	t_token	*returnable;

	returnable = temp->next;
	returnable->prev = NULL;
	temp->next = NULL;
	if (temp->prev)
	{
		temp->prev->next = NULL;
		free_token(&temp);
	}
	temp = advanced_tokenization(*command_first, term, 1);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tokens(*command_first, "advanced_tokenization in semi");
	root = ast_creator(temp, term);
	execute(root, term);
	*command_first = NULL;
	return (returnable);
}

t_token	*check_semicolon(t_token *first, t_term *term)
{
	t_token	*temp;
	t_token	*returnable;
	t_token	*command_first;

	temp = first;
	returnable = first;
	command_first = NULL;
	while (temp)
	{
		if (!command_first)
			command_first = temp;
		if (temp->maintoken == tkn_semi && temp->next)
		{
			returnable = run_semicolon_command(&command_first, term, temp);
			temp = returnable;
		}
		else if (temp->maintoken == tkn_semi && !temp->next && temp->prev)
		{
			temp->prev->next = NULL;
			free_token(&temp);
		}
		else
			temp = temp->next;
	}
	return (returnable);
}
