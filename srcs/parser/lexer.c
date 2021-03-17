/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/03/17 09:22:26 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
# include "libft.h"

void	check_token(t_token *current)
{
	if (ft_strchr(OPCHARS, current->value[0]))
		current->token = tkn_operator;
	else
		current->token = tkn_word;
}

t_token	*lexer(char *input)
{
	t_token	*first;
	t_token	*current;
	t_token	*prev;
	char	*str_ptr;
	
	prev = NULL;
	first = NULL;
	current = NULL;
	str_ptr = input;
	current = get_token(METACHARS, &str_ptr);
	while (current)
	{
		check_token(current);
		current->prev = prev;
		if (!prev)
			first = current;
		else
			prev->next = current;
		prev = current;
		current = get_token(METACHARS, &str_ptr);
	}
	return (first);
}
