/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:49:09 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/31 15:23:12 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	quote_removal(t_token *first)
{
	t_token	*temp;

	temp = first;
	while (temp)
	{
		if (temp->single_quoted)
			ft_remove_chars(temp->value, 39);
		if (temp->double_quoted)
			ft_remove_chars(temp->value, 34);
		temp = temp->next;
	}
}
