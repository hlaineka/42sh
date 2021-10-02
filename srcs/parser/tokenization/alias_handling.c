/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:02:17 by hlaineka          #+#    #+#             */
/*   Updated: 2021/10/02 12:27:32 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"
#include "includes.h"

static int	check_first_word(t_alias *a, t_token **temp, t_term *term,
	t_token **first)
{
	char		**original_commands;
	int			returnable;

	returnable = init_check_first_word(&original_commands, *temp);
	a = find_alias_with_name((*temp)->value, term->alias);
	while (a)
	{
		if (-1 == check_and_add_alias(original_commands, a, &returnable))
			break ;
		if (a && a->value)
			*temp = parse_new_command(a, term, first, temp);
		if (!*temp)
			break ;
		if (returnable == 1)
			returnable = 0;
		a = find_alias_with_name((*temp)->value, term->alias);
	}
	ft_strarray_free(original_commands);
	return (returnable);
}

t_token	*alias_handling(t_token *first, t_term *term, t_alias *a)
{
	t_token		*temp;
	int			first_word;
	t_token		*next;

	if (!first)
		return (NULL);
	temp = first;
	first_word = 1;
	while (temp && term)
	{
		next = temp->next;
		if (first_word)
			first_word = check_first_word(a, &temp, term, &first);
		if (temp && (temp->maintoken == tkn_and || temp->maintoken == tkn_pipe
				|| temp->maintoken == tkn_semi || temp->maintoken == tkn_and_if
				|| temp->maintoken == tkn_or_if || first_word == 2))
			first_word = 1;
		else
			first_word = 0;
		if (temp)
			temp = temp->next;
		temp = next;
	}
	return (first);
}
