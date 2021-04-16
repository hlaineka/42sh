/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:48:16 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/16 11:18:16 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"

t_node	*init_node(void)
{
	t_node	*returnable;

	returnable = malloc(sizeof(t_node));
	ft_bzero(returnable, sizeof(t_node));
	returnable->parent = NULL;
	returnable->left = NULL;
	returnable->right = NULL;
	returnable->command = NULL;
	return (returnable);
}

int	push_word(t_token *tkn, t_node **node_stack)
{
	int		i;
	t_node	*new_node;

	i = 0;
	while (node_stack[i] && i < 30)
		i++;
	if (i == 30)
	{
		ft_printf_fd(2, "node stack full");
		return (-1);
	}
	new_node = init_node();
	new_node->command = ft_strdup(tkn->value);
	new_node->operation = tkn->maintoken;
	delete_token(tkn);
	node_stack[i] = new_node;
	return (0);
}

int	is_unaryop(t_token *tkn)
{
	if (tkn->maintoken == tkn_less || tkn->maintoken == tkn_great
		|| tkn->maintoken == tkn_dless || tkn->maintoken == tkn_dgreat
		|| tkn->maintoken == tkn_lessand || tkn->maintoken == tkn_greatand
		|| tkn->maintoken == tkn_lessgreat || tkn->maintoken == tkn_clobber)
		return (1);
	return (0);
}

t_node	*create_opnode(t_token *tkn, t_node **node_stack, int *i)
{
	t_node	*new_node;

	new_node = init_node();
	new_node->command = ft_strdup(tkn->value);
	new_node->operation = tkn->maintoken;
	new_node->subtokens = tkn->subtokens;
	if (is_unaryop(tkn))
		new_node->right = NULL;
	else
	{
		*i = *i - 1;
		new_node->right = node_stack[*i];
		node_stack[*i]->parent = new_node;
	}
	return (new_node);
}

int	push_operator(t_token *tkn, t_node **node_stack)
{
	int		i;
	t_node	*new_node;

	i = 0;
	while (node_stack[i] && i < 30)
		i++;
	if (i == 30)
	{
		ft_printf_fd(2, "node stack full");
		return (-1);
	}
	new_node = create_opnode(tkn, node_stack, &i);
	if (i > 0)
	{
		node_stack[i] = NULL;
		new_node->left = node_stack[--i];
		node_stack[i]->parent = new_node;
	}
	node_stack[i] = NULL;
	node_stack[i] = new_node;
	delete_token(tkn);
	return (0);
}

t_node	*ast_builder(t_token *new_first)
{
	t_node	*node_stack[30];
	t_token	*temp;

	temp = NULL;
	ft_bzero(node_stack, sizeof(t_node *) * 30);
	while (new_first)
	{
		temp = new_first->next;
		if (new_first->precedence == 0)
		{
			if (-1 == (push_word(new_first, node_stack)))
				return (NULL);
		}
		else
			push_operator(new_first, node_stack);
		new_first = temp;
	}
	if (node_stack[1])
	{
		ft_printf_fd(2, "syntax error");
		return (NULL);
	}
	return (node_stack[0]);
}
