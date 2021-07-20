/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:35:28 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/11 17:04:36 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"

t_token	*bang_history(t_token *first, t_term *term)
{
	t_token	*temp;
	char	history[STR_LENGTH];
	int		i;

	temp = first;
	while (temp && term)
	{
		if (temp->value && temp->value[0] == '!' && !temp->quotes[0])
		{
			ft_bzero(history, STR_LENGTH);
			i = 1;
			while (temp->value[i])
			{
				history[i - 1] = temp->value[i];
				i++;
			}
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
			ft_printf_fd(STDOUT_FILENO, "value in history: -%s-\n", history);
		}
		temp = temp->next;
	}
	return (first);
}