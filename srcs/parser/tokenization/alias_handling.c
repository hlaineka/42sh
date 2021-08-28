/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/08/28 18:06:37 by hhuhtane         ###   ########.fr       */
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
	t_token		*new2;
	t_alias		*alias_cmd_s;
	int			eka;

	temp = first;
	prev = NULL;
	eka = 1;
	while (temp && term)
	{
		next = temp->next;
		alias_cmd_s = find_alias_with_name(temp->value, term->alias);
		if (alias_cmd_s && eka)
		{
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
//		temp = NULL;
	}
	return (first);
}
