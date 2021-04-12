/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/04/10 15:16:34 by hlaineka         ###   ########.fr       */
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
	if (current)
		free_token(current);
	return (returnable);
}

int	get_escchar_value(int c)
{
	if (c == '0')
		return ('\0');
	if (c == 'n')
		return ('\n');
	if (c == 'r')
		return ('\r');
	if (c == 't')
		return ('\t');
	if (c == 'b')
		return ('\b');
	if (c == 'f')
		return ('\f');
	if (c == 'v')
		return ('\v');
	if (c == 'r')
		return ('\r');
	return (c);
}

/*
** ascii 92 == \
*/

char	*replace_escchar(char *str, int i)
{
	int	w;

	w = i;
	while (str[i])
	{
		if (str[i] == 92)
		{
			i++;
			if (str[i] == '\n')
				i++;
			else
				str[i] = get_escchar_value(str[i]);
		}
		str[w] = str[i];
		w++;
		i++;
	}
	while (w < i)
		str[w++] = '\0';
	return (str);
}

char	*handle_backslash(char *input)
{
	int		i;
	char	*returnable;

	returnable = input;
	i = 0;
	while (returnable && returnable[i])
	{
		if (returnable[i] == 92)
			returnable = replace_escchar(returnable, i);
		i++;
	}
	return (returnable);
}


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
	input = handle_backslash(input);
	first = define_basic_tokens(input);
	if (term->flag_debug == 1)
		debug_print_tokens(first);
	first = define_operator_tokens(first);
	first = io_numbers(first);
	//alias handling call
	//reserved words recognition call
	//positional parameteres check call
	//special parameters and substitution, word expansions
	//field splitting = extra empty character removal that came from expansions & aliases
	//pathname extensions
	if (!first)
		return (NULL);
	quote_removal(first);
	//redirection (marking or handling?)
	return (first);
}
