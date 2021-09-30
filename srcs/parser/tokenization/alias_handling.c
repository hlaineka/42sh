/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/28 20:59:22 by hlaineka         ###   ########.fr       */
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

static int	check_first_word(t_alias *a, t_token *temp, t_term *term,
	t_token **first)
{
	t_token		*new;
	t_alias		*original_command;
	int			returnable;
	int			first_round;

	new = NULL;
	a = find_alias_with_name(temp->value, term->alias);
	original_command = a;
	returnable = 0;
	first_round = 1;
	while (a)
	{
		if (!first_round && a == original_command)
			break ;
		if (a && a->value)
		{
			if (!a->value[0])
				a->value[0] = '\n';
			new = lexer(ft_strdup(a->value), term, 0);
			*first = substitute_token(*first, new, temp);
			temp = new;
			returnable = 2;
		}
		if (!temp)
			break ;
		a = find_alias_with_name(temp->value, term->alias);
		first_round = 0;
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
