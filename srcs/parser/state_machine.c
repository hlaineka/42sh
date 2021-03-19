/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:33:13 by helvi             #+#    #+#             */
/*   Updated: 2021/03/18 21:27:44 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

handler g_states[4][40] = {
	{NULL, complete_word, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};

t_node	*tree_maker(t_token *tokens)
{
	t_token	*current_token;
	handler	next_function;
	t_node	*root;
	t_node	*current_node;

	current_token = tokens;
	root = initiate_node();
	current_node = root;
	while(current_token)
	{
		while (current_node && !(next_function = g_states[current_node->state][current_token->maintoken]))
		{
			current_node = current_node->parent;
		}
		if (!current_node)
		{
			ft_printf_fd("syntax error near token %s", current_token->value);
			//free nodes
			return (NULL);
		}
		if (-1 == (next_function(current_node, current_token)))
			{
				//free nodes
				return(NULL);
			}
		}
		current_token = current_token->next;
	}
}