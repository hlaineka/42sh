/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:11:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/28 15:47:23 by hlaineka         ###   ########.fr       */
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

static void	debug_printing(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_printf("tokens after shunting yard:\n");
	while (temp)
	{
		ft_printf("%s, ", temp->value);
		temp = temp->next;
	}
	ft_printf("\n");
}

t_node	*ast_creator(t_token *first, t_term *term)
{
	t_token	*new_first;
	t_node	*root;

	if (!first)
		return (NULL);
	root = NULL;
	new_first = add_precedence(first);
	new_first = shunting_yard(first);
	if (!new_first)
		return (NULL);
	if (term->flag_debug == 1)
		debug_printing(new_first);
	root = ast_builder(new_first);
	return (root);
}
