/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 16:47:29 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/28 17:04:06 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*remove_token(t_token **remove)
{
	t_token		*next;
	t_token		*prev;

	next = remove[0]->next;
	prev = remove[0]->prev;
	remove[0]->next = NULL;
	remove[0]->prev = NULL;
	free_tokens(remove);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	*remove = next;
	return (next);
}
