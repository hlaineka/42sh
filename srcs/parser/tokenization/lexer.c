/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/04/01 12:46:38 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_token	*define_basic_tokens(char *input)
{
	t_token	*current;
	t_token	*prev;
	t_token	*returnable;
	char	*str_ptr;

	current = NULL;
	prev = NULL;
	str_ptr = input;
	returnable = NULL;
	current = get_basic_token(METACHARS, &str_ptr);
	while (current && current->value && current->value[0])
	{
		current->prev = prev;
		if (!prev)
		{
			returnable = current;
			//assignment_word check
		}
		else
			prev->next = current;
		prev = current;
		current = get_basic_token(METACHARS, &str_ptr);
	}
	return (returnable);
}

t_token	*lexer(char *input)
{
	t_token	*first;

	first = NULL;
	first = define_basic_tokens(input);
	first = define_operator_tokens(first);
	if (!first)
		return (NULL);
	//comment handling here.
	//IO_NUMBER handling
	//alias handling call
	//reserved words recognition call
	//positional parameteres check call
	//special parameters and substitution, word expansions
	//field splitting = extra empty character removal that came from expansions & aliases
	//pathname extensions
	quote_removal(first);
	//redirection (marking or handling?)
	return (first);
}
