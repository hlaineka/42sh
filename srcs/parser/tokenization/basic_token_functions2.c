/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:54:13 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/14 16:27:56 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_token		*init_token(void)
{
	t_token	*returnable;

	returnable = (t_token *)malloc(sizeof(t_token));
	ft_bzero(returnable, sizeof(t_token));
	returnable->value = NULL;
	returnable->subtokens = NULL;
	returnable->next = NULL;
	returnable->prev = NULL;
	return (returnable);
}

t_token	*add_subtoken(t_token *current, t_token *sub)
{
	t_token	*returnable;
	t_token	*temp;

	if (!current)
		return (NULL);
	if (!sub)
		return (NULL);
	if (sub->prev)
		sub->prev->next = sub->next;
	if (sub->next)
		sub->next->prev = sub->prev;
	sub->next = NULL;
	returnable = current;
	temp = current->subtokens;
	if (temp)
	{
		while(temp->next)
			temp = temp->next;
		temp->next = sub;
		sub->prev = temp;
	}
	else
	{
		returnable->subtokens = sub;
		sub->prev = returnable;
	}
	return(returnable);
}
