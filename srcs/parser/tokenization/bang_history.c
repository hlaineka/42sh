/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:35:28 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/25 12:35:49 by hlaineka         ###   ########.fr       */
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
			ft_printf_fd(STDOUT_FILENO, "value in history: -%s-\n", temp->value);
			new = lexer(ft_strdup(history_cmd), term, 0);
			free_tokens(temp->subtokens);
			delete_token(temp);
			if (prev)
				prev->next = new;
			else
				first = new;
			temp = new;
			while (temp->next)
				temp = temp->next;
			temp->next = next;
			// call to history function here, with const char *history as parameter
			// now if ! is the first and unquoted char of string, we get here. Is this the rule?
			// ft_free(temp->value);
			// temp->value = get_history(history, term);
			// what is returned if no history is found? Do we need an error check here?
			// if (!temp->value)
			// free_tokens(first);
			// print error message;
			// return (null);
			// remove the next line
		}
		prev = temp;
		temp = next;
	}
	return (first);
}
