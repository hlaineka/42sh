/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:11:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/27 11:19:26 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
# include <stdbool.h>

/*
** When there are two plain words one after another, a delimiter token needs to be
** added to make sure the bind together in the shunting yard algorithm.
*/

t_token		*add_delimiter_token(t_token *tkn)
{
	t_token *new;
	t_token *returnable;
	
	new = (t_token*)malloc(sizeof(t_token));
	ft_bzero(new, sizeof(t_token));
	returnable = tkn->next;
	new->single_quoted = FALSE;
	new->double_quoted = FALSE;
	new->precedence = 5;
	tkn->next->prev = new;
	new->next = tkn->next;
	tkn->next = new;
	new->prev = tkn;
	return (returnable);
}

t_token		*add_precedence(t_token *first)
{
	t_token	*temp;
	t_token *returnable;

	temp = first;
	returnable = first;
	while(temp)
	{
		if (temp->maintoken == tkn_word && temp->next && temp->next->maintoken == tkn_word)
			temp = add_delimiter_token(temp);
		else if (temp->maintoken == tkn_less || temp->maintoken == tkn_great
		|| temp->maintoken == tkn_less || temp->maintoken == tkn_great
		|| temp->maintoken == tkn_lessand || temp->maintoken == tkn_greatand
		|| temp->maintoken == tkn_lessgreat || temp->maintoken == tkn_dlessdash
		|| temp->maintoken == tkn_clobber)
			temp->precedence = 4;
		else if (temp->maintoken == tkn_pipe)
			temp->precedence = 3;
		else if (temp->maintoken == tkn_and_if || temp->maintoken == tkn_or_if)
			temp->precedence = 2;
		else if (temp->maintoken == tkn_semi || temp->maintoken == tkn_and)
			temp->precedence = 1;
		if (temp->maintoken == tkn_pipe || temp->maintoken == tkn_and_if || temp->maintoken == tkn_or_if)
			temp->left_associative = TRUE;
		else
			temp->left_associative = FALSE; //I think this can be left out when initialized as zero
		temp = temp->next;
	}
	return (returnable);
}

t_token		*push_to_output(t_token *input, t_token *output)
{
	t_token	*returnable;
	t_token	*temp;

	returnable = output;
	temp = output;
	if (!output)
	{
		//ft_printf("push to output: output is NULL\n");
		returnable = input;
		returnable->next = NULL;
		returnable->prev = NULL;
	}
	else
	{
		//ft_printf("adding to output list\n");
		while (temp->next)
			temp = temp->next;
		temp->next = input;
		input->next = NULL;
		input->prev = temp;
	}
	return (returnable);
}

t_token		*push_to_stack(t_token *input, t_token *stack)
{
	input->next = NULL;
	input->prev = stack;
	if (stack)
		stack->next = input;
	return (input);
}

t_token		*delete_token(t_token *tkn)
{
	t_token *returnable;
	
	returnable = NULL;
	ft_free(tkn->tokens);
	ft_free(tkn->value);
	if (tkn->next)
	{
		tkn->next->prev = tkn->prev;
		returnable = tkn->next;
	}
	if (tkn->prev)
	{
		tkn->prev->next = tkn->next;
		if (!returnable)
			returnable = tkn->prev;
	}
	ft_free(tkn);
	return (returnable);
}

//funtions need to be added separately. They will need their own token.

t_token		*handle_operator(t_token **op_stack, t_token **input, t_token *output)
{
	t_token *returnable;
	t_token	*temp;

	returnable = output;
	if ((*input)->maintoken == tkn_lpar)
	{
		//ft_printf("left paranthesis\n");
		*op_stack = push_to_stack(*input, *op_stack);
	}
	else if ((*input)->maintoken == tkn_rpar)
	{
		//ft_printf("right paranthesis\n");
		while (*op_stack && (*op_stack)->maintoken != tkn_lpar)
		{
			temp = (*op_stack)->prev;
			returnable = push_to_output(*op_stack, returnable);
			*op_stack = temp;
		}
		if (!(*op_stack))
		{
			//ft_printf_fd(2, "syntax error, wrong amount of paranthesis");
			return (NULL);
		}
		*input = delete_token(*input);
		*op_stack = delete_token(*op_stack);
	}
	else
	{
		//ft_printf("handle other operators than paranthesis\n");
		while (*op_stack && ((*op_stack)->precedence > (*input)->precedence || ((*op_stack)->precedence == (*input)->precedence && (*input)->left_associative)))
		{	
			temp = (*op_stack)->prev;
			//ft_printf("in while, pushing from op_stack to output. %s\n", (*op_stack)->value);
			returnable = push_to_output(*op_stack, returnable);
			*op_stack = temp;
		}
		//ft_printf("Pushing from input to op_stack.");
		//if (*input)
		//	ft_printf("%s", (*input)->value);
		//ft_printf("\n");
		*op_stack = push_to_stack(*input, *op_stack);
	}
	return(returnable);
}

t_token		*shunting_yard(t_token *first)
{
	t_token	*op_stack;
	t_token	*output;
	t_token	*input;
	t_token *temp;

	temp = NULL;
	op_stack = NULL;
	output = NULL;
	input = first;
	while (input)
	{
		temp = input->next;
		//ft_printf("read new token\n");
		if (input->precedence == 0)
		{
			//ft_printf("add tkn_word to output\n");
			output = push_to_output(input, output);
		}
		else
		{	
			//ft_printf("handle operator\n");
			output = handle_operator(&op_stack, &input, output);
		}
		if (output == NULL)
		{
			//ft_printf("output in NULL\n");
			return (NULL);
		}
		input = temp;
	}
	while (op_stack)
	{
		temp = op_stack->prev;
		//ft_printf("push rest of the op_stack to output\n");
		push_to_output(op_stack, output);
		op_stack = temp;
	}
	return (output);
}

static void	debug_printing(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		ft_printf("precedence: %i, value: %s. ", temp->precedence, temp->value);
		temp = temp->next;
		ft_printf("\n");
	}
	ft_printf("\n");
}

t_token		*ast_creator(t_token *first, bool debug)
{
	t_token	*new_first;

	new_first = add_precedence(first);
	new_first = shunting_yard(first);
	if (debug)
		debug_printing(new_first);
	return (new_first);
}