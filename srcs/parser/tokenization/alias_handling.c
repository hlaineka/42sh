/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/11 17:39:05 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"

t_token				*alias_handling(t_token *first, t_term *term, t_alias *a)
{
	t_token		*temp;
	t_token		*next;
	t_token		*prev;
	t_token		*new;
	int			first_word;

	temp = first;
	prev = first->prev;
	first_word = 1;
	new = NULL;
	while (temp && term)
	{
		next = temp->next;
		if (first_word)
		{
			a = find_alias_with_name(temp->value, term->alias);
			if (a && a->value && a->value[0])
			{
				new = lexer(ft_strdup(a->value), term, 0);
				free_tokens(&(temp->subtokens));
				delete_token(temp);
				if (prev)
					prev->next = new;
				else
					first = new;
				new->prev = prev;
				while (new->next)
					new = new->next;
				new->next = next;
				if (next)
					next->prev = new;
			}
		}
		if (temp->maintoken == tkn_and || temp->maintoken == tkn_pipe
			|| temp->maintoken == tkn_semi || temp->maintoken == tkn_and_if
			|| temp->maintoken == tkn_or_if)
			first_word = 1;
		else
			first_word = 0;
		prev = temp;
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
