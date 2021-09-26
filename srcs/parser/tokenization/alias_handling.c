/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 21:22:43 by hlaineka         ###   ########.fr       */
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
	delete_token(current);
	if (prev)
		prev->next = new;
	else
		returnable = new;
	new->prev = prev;
	while (new->next)
		new = new->next;
	new->next = next;
	if (next)
		next->prev = new;
	return (returnable);
}

static int	check_first_word(t_alias *a, t_token *temp, t_term *term,
	t_token **first)
{
	t_token		*new;
	t_alias		*original_command;
	int			returnable;

	new = NULL;
	a = find_alias_with_name(temp->value, term->alias);
	original_command = a;
	returnable = 0;
	while (a)
	{
		if (a && a->value && a->value[0])
		{
			new = lexer(ft_strdup(a->value), term, 0);
			*first = substitute_token(*first, new, temp);
			temp = new;
			returnable = 2;
		}
		a = find_alias_with_name(temp->value, term->alias);
		if (a == original_command)
			break ;
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
