/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:07:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/11 15:58:59 by hlaineka         ###   ########.fr       */
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

t_token	*handle_braces(t_token **op_stack, t_token **input,
		t_token *output)
{
	t_token	*returnable;
	t_token	*temp;

	returnable = output;
	if ((*input)->maintoken == tkn_lbrace)
		*op_stack = push_to_front(*input, *op_stack);
	else if ((*input)->maintoken == tkn_rbrace)
	{
		while (*op_stack && (*op_stack)->maintoken != tkn_lbrace)
		{
			temp = (*op_stack)->prev;
			returnable = push_to_end(*op_stack, returnable);
			*op_stack = temp;
		}
		if (!(*op_stack))
		{
			ft_printf_fd(STDERR_FILENO, "wrong amount of braces\n");
			return (NULL);
		}
		temp = (*op_stack)->prev;
		returnable = push_to_end(*op_stack, returnable);
		*op_stack = temp;
		returnable = push_to_end(*input, returnable);
	}
	return (returnable);
}

t_token	*handle_parenthesis(t_token **op_stack, t_token **input,
		t_token *output)
{
	t_token	*returnable;
	t_token	*temp;

	returnable = output;
	if ((*input)->maintoken == tkn_lpar || (*input)->maintoken == tkn_dollarlpar)
		*op_stack = push_to_front(*input, *op_stack);
	else if ((*input)->maintoken == tkn_rpar)
	{
		while (*op_stack && (*op_stack)->maintoken != tkn_lpar
			&& (*op_stack)->maintoken != tkn_dollarlpar)
		{
			temp = (*op_stack)->prev;
			returnable = push_to_end(*op_stack, returnable);
			*op_stack = temp;
		}
		if (!(*op_stack))
		{
			ft_printf_fd(STDERR_FILENO, "wrong amount of paranthesis\n");
			return (NULL);
		}
		temp = (*op_stack)->prev;
		returnable = push_to_end(*op_stack, returnable);
		*op_stack = temp;
		returnable = push_to_end(*input, returnable);
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
	else if ((*input)->maintoken == tkn_lbrace || (*input)->maintoken == tkn_rbrace)
		returnable = handle_braces(op_stack, input, output);
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
	//ft_printf("end of handle operator\n");
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
		if (input->precedence == 0 && input->maintoken != tkn_lpar
		&& input->maintoken != tkn_rpar && input->maintoken != tkn_lbrace
		&& input->maintoken != tkn_rbrace && input->maintoken != tkn_dollarlpar)
			output = push_to_end(input, output);
		else
			output = handle_operator(&op_stack, &input, output);
		input = temp;
		if (!output)
		{
			delete_tokens(op_stack);
			delete_tokens(output);
			delete_tokens(first);
			return (NULL);
		}
		//ft_printf("end of while (input)\n");
	}
	//ft_printf("after while (input\n");
	while (op_stack)
	{
		temp = op_stack->prev;
		output = push_to_end(op_stack, output);
		op_stack = temp;
		//ft_printf("endo of while (op_stack\n");
	}
	//ft_printf("after while(op_stack)\n");
	return (output);
}
