/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_assignment_marking.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:39:32 by hlaineka          #+#    #+#             */
/*   Updated: 2021/06/30 16:21:36 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

t_token	*word_assignment_marking(t_token *first)
{
	t_token *temp;
	int		i_equal_sign;
	int		i;
	char	*name;

	temp = first;
	while (temp)
	{
		i_equal_sign = ft_str_find_c(temp->value, '=');
		if (i_equal_sign > 0 && temp->quotes[i_equal_sign] == 0)
		{
			name = malloc(i_equal_sign + 1);
			i = 0;
			while (i < i_equal_sign)
			{
				if (first->quotes[i] != 0)
				{
					ft_free(name);
					break;
				}
				name[i] = first->value[i];
				i++;
			}
			name[i] = '\0';
			if (ft_is_name(name))
				temp->maintoken = tkn_assignment_word;
			ft_free(name);
		}
		temp = temp->next;
	}
	return (first);
}
