/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_assignment_marking.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:39:32 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/01 13:29:20 by hlaineka         ###   ########.fr       */
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
	int		nth_command;
	char	*name;

	temp = first;
	nth_command = 0;
	while (temp)
	{
		if (temp->maintoken == tkn_and || temp->maintoken == tkn_semi
		|| temp->maintoken == tkn_nl || temp->maintoken == tkn_pipe
		|| temp->maintoken == tkn_and_if || temp->maintoken == tkn_or_if
		|| temp->maintoken == tkn_dsemi)
			nth_command = 0;
		else
			nth_command++;
		i_equal_sign = ft_str_find_c(temp->value, '=');
		if (i_equal_sign > 0 && temp->quotes[i_equal_sign] == 0 && nth_command == 1)
		{
			nth_command = 0;
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
