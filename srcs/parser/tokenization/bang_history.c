/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:35:28 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/25 18:22:13 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"
#include "history.h"

t_token	*bang_history(t_token *first, t_term *term)
{
	t_token		*temp;
	t_token		*next;
	t_token		*prev;
	t_token		*new;
	const char	*history_cmd;

	temp = first;
	prev = NULL;
	while (temp && term)
	{
		next = temp->next;
		if (temp->value && temp->value[0] == '!' && !temp->quotes[0])
		{
			history_cmd = bang_selector(temp->value, term);
			if (!history_cmd)
			{
				ft_printf_fd(2, "history not found\n");
				free_tokens(first);
				return (NULL);
			}
			//ft_printf_fd(STDOUT_FILENO, "value in history: -%s-\n", history_cmd);
			new = lexer(ft_strdup(history_cmd), term, 0);
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
			if (next)
				next->prev = temp;
		}
		prev = temp;
		temp = next;
	}
	return (first);
}
