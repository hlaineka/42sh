/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:11:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/12 10:44:41 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "includes.h"
#include <stdbool.h>

/*
** The main function for abstract syntax tree creation. First precendance value
** is added to the tokens with null tokens that are used to combine two words
** together. After that the tokens are send to shunting yard, and algorithm
** that changes the infix notation to postfix notation. The abstarct syntax
** tree creation is much easier from postfic notation. The tokens are printed
** out after the shunting yard if the shell was started in debug mode. In the
** end, the abstract syntax tree is created.
** Parameters: first of the token list, the "global" struct term
** Return value: the root of the abstract syntax tree.
*/

static void	debug_printing(t_token *tokens, char *function_name)
{
	t_token	*temp;

	temp = tokens;
	ft_printf_fd(STDOUT_FILENO, "tokens after %s:\n", function_name);
	while (temp)
	{
		ft_printf_fd(STDOUT_FILENO, "%s p=%i, ", temp->value, temp->precedence);
		temp = temp->next;
	}
	ft_printf_fd(STDOUT_FILENO, "\n");
}

t_node	*ast_creator(t_token *first, t_term *term)
{
	t_node	*root;

	if (!first)
		return (NULL);
	root = NULL;
	first = add_precedence(first);
	if (term->intern_variables->flag_debug == 1)
		debug_printing(first, "add_precedence");
	first = shunting_yard(first);
	if (!first)
		return (NULL);
	if (term->intern_variables->flag_debug == 1)
		debug_printing(first, "shunting_yard");
	root = ast_builder(first);
	free_tokens(&first);
	return (root);
}
