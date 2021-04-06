/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:07:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/31 15:21:54 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** Shunting yard is an algorithm used to produce postfix notation form infix
** notations. In our implementation postfix was selected because of the ease
** to transform it to binary tree. Shunting yard uses a last in first out
** stack to store operators, and compares the precedence values to evaluate
** when an operator is moved from operator stack to output. More about the
** algorithm https://en.wikipedia.org/wiki/Shunting-yard_algorithm
** NOTES:
** funtions need to be added separately. They will need their own token.
*/

t_token	*handle_parenthesis(t_token **op_stack, t_token **input,
		t_token *output)
{
	t_token	*returnable;
	t_token	*temp;

	returnable = output;
	if ((*input)->maintoken == tkn_lpar)
		*op_stack = push_to_front(*input, *op_stack);
	else if ((*input)->maintoken == tkn_rpar)
	{
		while (*op_stack && (*op_stack)->maintoken != tkn_lpar)
		{
			temp = (*op_stack)->prev;
			returnable = push_to_end(*op_stack, returnable);
			*op_stack = temp;
		}
		if (!(*op_stack))
		{
			ft_printf_fd(2, "wrong amount of paranthesis");
			return (NULL);
		}
		*input = delete_token(*input);
		*op_stack = delete_token(*op_stack);
	}
	return (returnable);
}

t_token	*handle_operator(t_token **op_stack, t_token **input, t_token *output)
{
	t_token	*returnable;
	t_token	*temp;

	returnable = output;
	if ((*input)->maintoken == tkn_lpar || (*input)->maintoken == tkn_rpar)
		returnable = handle_parenthesis(op_stack, input, output);
	else
	{
		while (*op_stack && ((*op_stack)->precedence > (*input)->precedence
				|| ((*op_stack)->precedence == (*input)->precedence
					&& (*input)->left_associative)))
		{	
			temp = (*op_stack)->prev;
			returnable = push_to_end(*op_stack, returnable);
			*op_stack = temp;
		}
		*op_stack = push_to_front(*input, *op_stack);
	}
	return (returnable);
}

t_token	*shunting_yard(t_token *first)
{
	t_token	*op_stack;
	t_token	*output;
	t_token	*input;
	t_token	*temp;

	temp = NULL;
	op_stack = NULL;
	output = NULL;
	input = first;
	while (input)
	{
		temp = input->next;
		if (input->maintoken == 1)
			output = push_to_end(input, output);
		else
			output = handle_operator(&op_stack, &input, output);
		input = temp;
	}
	while (op_stack)
	{
		temp = op_stack->prev;
		push_to_end(op_stack, output);
		op_stack = temp;
	}
	return (output);
}
