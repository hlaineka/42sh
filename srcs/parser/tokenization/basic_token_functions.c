/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 12:58:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 20:55:14 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** Functions to help basic tokenization
*/

t_token	*delete_tokens(t_token *tkn)
{
	t_token	*temp;
	t_token	*next;

	temp = tkn;
	next = NULL;
	while (temp)
	{
		next = temp->next;
		free_tokens(&(temp->subtokens));
		free_token(&temp);
		temp = next;
	}
	return (NULL);
}

t_token	*delete_token(t_token *tkn)
{
	t_token	*returnable;

	returnable = NULL;
	if (tkn->value)
		ft_memdel((void **)&tkn->value);
	if (tkn->quotes)
		ft_memdel((void **)&tkn->quotes);
	if (tkn->full_command)
		ft_memdel((void **)&tkn->full_command);
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
	ft_memdel((void **)&tkn);
	return (returnable);
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	while (*tokens)
	{
		temp = tokens[0]->next;
		free_token(tokens);
		tokens[0] = temp;
	}
}

void	free_token(t_token **to_free)
{
	if (to_free[0]->value)
		ft_memdel((void **)(&to_free[0]->value));
	if (to_free[0]->quotes)
		ft_memdel((void **)&to_free[0]->quotes);
	if (to_free[0]->full_command)
		ft_memdel((void **)&to_free[0]->full_command);
	ft_memdel((void **)to_free);
	to_free[0] = NULL;
}

void	free_tokens_sub(t_token *tokens)
{
	t_token	*temp;
	t_token	*temp_sub;
	t_token	*next_temp;
	t_token	*next_temp_sub;

	temp = tokens;
	while (temp)
	{
		next_temp = temp->next;
		temp_sub = temp->subtokens;
		while (temp_sub)
		{
			next_temp_sub = temp_sub->next;
			free_token(&temp_sub);
			temp_sub = next_temp_sub;
		}
		free_token(&temp);
		temp = next_temp;
	}
}
