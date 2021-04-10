/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:08:23 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/08 15:17:36 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

bool	ft_is_nbrstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_token	*io_numbers(t_token *first)
{
	t_token	*temp;
	t_token	*returnable;

	if (!first)
		return (first);
	temp = first;
	returnable = first;
	while(temp)
	{
		if (temp->maintoken == tkn_less || temp->maintoken == tkn_great
		|| temp->maintoken == tkn_dless || temp->maintoken == tkn_dgreat
		|| temp->maintoken == tkn_lessand || temp->maintoken == tkn_greatand
		|| temp->maintoken == tkn_lessgreat)
		{
			if (temp->prev && ft_is_nbrstr(temp->prev->value))
			{
				temp->prev->maintoken = tkn_io_number;
				if (!temp->prev->prev)
				returnable = temp;
				add_subtoken(temp, temp->prev);
			}
		}
		temp = temp->next;
	}
	return (returnable);
}