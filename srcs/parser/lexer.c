/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/03/15 10:33:58 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*lexer(char *input)
{
	t_list	*temp;
	t_list	*first;
	t_token	*current;
	char	*next_tkn_pointer;
	char	*str_ptr;
	
	if (!(current = (t_token*)malloc(sizeof(t_token))))
		die("malloc");
	ft_bzero(current, sizeof(t_token));
	next_tkn_pointer = NULL;
	temp = ft_lstnew(current, sizeof(t_token*));
	temp->next = NULL;
	first = temp;
	str_ptr = input;
	while (temp)
	{
		
		temp->next = ft_lstnew(current, sizeof(t_token*));
		current = (t_token*)temp->next->content;
		current->value = ft_strtok_r(str_ptr, METACHARS, &next_tkn_pointer);
		str_ptr = next_tkn_pointer;
		if (ft_strchr(OPCHARS, current->value[0]))
			current->token = tkn_operator;
		else
			current->token = tkn_word;
		temp = temp->next;
	}
	return (first);
}
