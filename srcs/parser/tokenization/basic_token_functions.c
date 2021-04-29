/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 12:58:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 10:02:44 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** Functions to help basic tokenization
*/

t_token	*push_to_front(t_token *input, t_token *stack)
{
	input->next = NULL;
	input->prev = stack;
	if (stack)
		stack->next = input;
	return (input);
}

t_token	*push_to_end(t_token *input, t_token *output)
{
	t_token	*returnable;
	t_token	*temp;

	returnable = output;
	temp = output;
	if (!output)
	{
		returnable = input;
		returnable->next = NULL;
		returnable->prev = NULL;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = input;
		input->next = NULL;
		input->prev = temp;
	}
	return (returnable);
}

t_token	*delete_token(t_token *tkn)
{
	t_token	*returnable;

	returnable = NULL;
	if (tkn->value)
		ft_free(tkn->value);
	if (tkn->quotes)
		ft_free(tkn->quotes);
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
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free_token(tokens);
		tokens = temp;
	}
}

void	free_token(t_token *to_free)
{
	if (to_free->value)
		ft_free(to_free->value);
	if (to_free->quotes)
		ft_free(to_free->quotes);
	ft_free(to_free);
	to_free = NULL;
}
