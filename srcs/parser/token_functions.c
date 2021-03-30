/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 12:58:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/27 13:23:42 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_token		*push_to_front(t_token *input, t_token *stack)
{
	input->next = NULL;
	input->prev = stack;
	if (stack)
		stack->next = input;
	return (input);
}

t_token		*push_to_end(t_token *input, t_token *output)
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

void	free_tokens(t_token *tokens)
{
	while(tokens)
		tokens = delete_token(tokens);
}