/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/04/12 10:21:48 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static void	debug_print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_printf("tokens after first tokenization:\n");
	while (temp)
	{
		ft_printf("%s = %i, ", temp->value, temp->maintoken);
		temp = temp->next;
	}
	ft_printf("\n");
}

t_token	*lexer(char *input, t_term *term)
{
	t_token	*first;

	first = NULL;
	first = define_basic_tokens(input);
	first = validate_operator_tokens(first);
	//first = io_numbers(first);
	//alias handling call
	//reserved words recognition call
	//positional parameteres check call
	//special parameters and substitution, word expansions
	//field splitting = extra empty character removal that came from expansions & aliases
	//pathname extensions
	if (term->flag_debug == 1)
		debug_print_tokens(first);
	if (!first)
		return (NULL);
	quote_removal(first);
	//redirection (marking or handling?)
	return (first);
}
