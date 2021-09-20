/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/12 08:53:12 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"
#include "includes.h"

t_token	*substitute_token(t_token *first, t_token *new, t_token *current)
{
	t_token *prev;
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

t_token				*alias_handling(t_token *first, t_term *term, t_alias *a)
{
	t_token		*temp;
	t_token		*next;
	t_token		*new;
	t_alias		*original_command;
	int			first_word;

	if (!first)
		return (NULL);
	temp = first;
	first_word = 1;
	new = NULL;
	while (temp && term)
	{
		next = temp->next;
		if (first_word)
		{
			a = find_alias_with_name(temp->value, term->alias);
			original_command = a;
			while (a)
			{
				if (a && a->value && a->value[0])
				{
					new = lexer(ft_strdup(a->value), term, 0);
					first = substitute_token(first, new, temp);
					temp = new;
				}
				a = find_alias_with_name(temp->value, term->alias);
				if (a == original_command)
					break;
			}
		}
		if (temp->maintoken == tkn_and || temp->maintoken == tkn_pipe
			|| temp->maintoken == tkn_semi || temp->maintoken == tkn_and_if
			|| temp->maintoken == tkn_or_if)
			first_word = 1;
		else
			first_word = 0;
		temp = next;
	}
	return (first);
}

/*
if (!a)
				a = alias_cmd_s;
			else if (a == alias_cmd_s)
				return (NULL);
			if (!alias_cmd_s->value[0])
			{
				if (temp == first)
				{
					first = remove_token(&temp);
				}
				else
					temp = remove_token(&temp);
//				first = first->next;
//				break ;
				continue ;
			}
			new = lexer(ft_strdup(alias_cmd_s->value), term, 0);
			new2 = alias_handling(new, term, a);
			if (!new2)
			{
				free_tokens(&new);
				if (a == alias_cmd_s)
					break ;
				return (NULL);
			}
			free_tokens(&temp->subtokens);
			delete_token(temp);
			if (!new2)
				break ;
			if (prev)
				prev->next = new2;
			else
				first = new2;
			new->prev = prev;
			temp = new2;
			while (temp->next)
				temp = temp->next;
			temp->next = next;
			if (next)
				next->prev = temp;
		}
		if (ft_strequ(temp->value, ";"))
			eka = 1;
		else
			eka = 0;
*/
