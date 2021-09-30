/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/30 20:10:59 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"
#include "includes.h"

static t_token	*substitute_token(t_token *first, t_token *new,
	t_token *current)
{
	t_token	*prev;
	t_token	*next;
	t_token	*returnable;

	returnable = first;
	prev = current->prev;
	next = current->next;
	free_tokens(&(current->subtokens));
	free_token(&current);
	if (prev)
		prev->next = new;
	else if (new)
		returnable = new;
	else
		returnable = next;
	if (new)
	{
		new->prev = prev;
		while (new->next)
			new = new->next;
		new->next = next;
	}
	if (next)
		next->prev = new;
	return (returnable);
}

int	check_and_add_alias(t_alias **original_commands, t_alias *a, int *first_word)
{
	int	i;

	i = 0;
	while (original_commands[i])
	{
		if (original_commands[i] == a)
			return (-1);
		i++;
	}
	original_commands[i] = a;
	if (a && (a->value[ft_strlen(a->value) - 1] == ' '
		|| a->value[ft_strlen(a->value) - 1] == '\t'
		|| a->value[ft_strlen(a->value) - 1] == '\n'))
		*first_word = 2;
	else
		*first_word = 0;
	return (0);
}

static int	check_first_word(t_alias *a, t_token *temp, t_term *term,
	t_token **first)
{
	t_token		*new;
	t_alias		*original_commands[STR_LENGTH];
	int			returnable;

	new = NULL;
	ft_bzero((void *)original_commands, (sizeof(t_alias *) * STR_LENGTH));
	a = find_alias_with_name(temp->value, term->alias);
	returnable = 1;
	while (a)
	{
		if (-1 == check_and_add_alias(original_commands, a, &returnable))
			break ;
		if (a && a->value)
		{
			if (!a->value[0])
				a->value[0] = ' ';
			new = lexer(ft_strdup(a->value), term, 0);
			*first = substitute_token(*first, new, temp);
			temp = new;
		}
		if (!temp)
			break ;
		if (returnable == 1)
			returnable = 0;
		a = find_alias_with_name(temp->value, term->alias);
	}
	return (returnable);
}

t_token	*alias_handling(t_token *first, t_term *term, t_alias *a)
{
	t_token		*temp;
	t_token		*next;
	int			first_word;

	if (!first)
		return (NULL);
	temp = first;
	first_word = 1;
	while (temp && term)
	{
		next = temp->next;
		if (first_word)
			first_word = check_first_word(a, temp, term, &first);
		if (temp->maintoken == tkn_and || temp->maintoken == tkn_pipe
			|| temp->maintoken == tkn_semi || temp->maintoken == tkn_and_if
			|| temp->maintoken == tkn_or_if || first_word == 2)
			first_word = 1;
		else
			first_word = 0;
		temp = next;
	}
	return (first);
}
