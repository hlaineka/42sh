/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:11:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/31 14:57:24 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "includes.h"
#include <stdbool.h>

static void	debug_printing(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_printf("tokens after shunting yard:\n");
	while (temp)
	{
		ft_printf("%s, ", temp->value);
		temp = temp->next;
	}
	ft_printf("\n");
}

t_node	*ast_creator(t_token *first, bool debug)
{
	t_token	*new_first;
	t_node	*root;

	if (!first)
		return (NULL);
	root = NULL;
	new_first = add_precedence(first);
	new_first = shunting_yard(first);
	if (!new_first)
		return (NULL);
	if (debug)
		debug_printing(new_first);
	root = ast_builder(new_first);
	return (root);
}
