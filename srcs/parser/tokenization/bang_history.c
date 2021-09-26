/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:35:28 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 20:12:59 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"
#include "history.h"

static t_token	*add_new_token(const char *history_cmd, t_term *term,
	t_token *first, t_token *temp)
{
	t_token		*new;
	t_token		*prev;
	t_token		*next;

	prev = temp->prev;
	next = temp->next;
	new = lexer(ft_strdup(history_cmd), term, 0);
	free_tokens(&temp->subtokens);
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
	if (next)
		next->prev = temp;
	return (first);
}

t_token	*bang_history(t_token *first, t_term *term)
{
	t_token		*temp;
	t_token		*next;
	const char	*history_cmd;

	temp = first;
	while (temp && term)
	{
		next = temp->next;
		if (temp->value && temp->value[0] == '!' && !temp->quotes[0])
		{
			history_cmd = bang_selector(temp->value, term);
			if (!history_cmd)
			{
				term->last_return = 1;
				ft_printf_fd(2, "42sh: %s: history event not found\n",
					temp->value);
				delete_tokens(first);
				return (NULL);
			}
			first = add_new_token(history_cmd, term, first, temp);
		}
		temp = next;
	}
	return (first);
}
