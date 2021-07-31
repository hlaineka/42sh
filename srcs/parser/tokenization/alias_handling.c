/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/29 19:38:25 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"

t_token				*alias_handling(t_token *first, t_term *term)
{
	t_token		*temp;
	t_token		*next;
	t_token		*prev;
	t_token		*new;
	const char	*alias_cmd;

	temp = first;
	prev = NULL;
	while (temp && term)
	{
		next = temp->next;

		alias_cmd = find_alias_named_name(temp->value, term->alias);
		if (alias_cmd)
		{
			new = lexer((char *)alias_cmd, term, 0);

			free_tokens(temp->subtokens);
			delete_token(temp);
			if (prev)
				prev->next = new;
			else
				first = new;
			new->prev = prev;
			temp = new;
			while (temp->next)
				temp = temp->next;
			temp->next = next;
			next->prev = temp;
		}

		/*
		// alias_checker ja alias_selector tekemättä, tai sitten ne voi yhdistääkin
		if (alias_checker(temp->value))
		{
			alias_cmd = alias_selector(temp->value, term);
			new = lexer(ft_strdup(alias_cmd), term, 0);
			free_tokens(temp->subtokens);
			delete_token(temp);
			if (prev)
				prev->next = new;
			else
				first = new;
			new->prev = prev;
			temp = new;
			while (temp->next)
				temp = temp->next;
			temp->next = next;
			next->prev = temp;
		}
		*/

		prev = temp;
		temp = next;
	}
	(void)next;
	(void)term;
	return (first);
}
