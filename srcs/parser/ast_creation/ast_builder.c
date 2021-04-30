/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:48:16 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/30 10:37:34 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"

/*
** The abstact syntax tree is created from postfix notation with the help of
** last in first out stack (made with pointers of the tokens). The command
** echo hi ; ls > file
** would become
** echo, hi, (null), ls, >, ;
** To create the abstract syntax tree, the tokens are read from right to left.
** all the words are moved to stack as nodes, so in this case we would have
** echo and hi. Next we have the operator null, which takes two parameters
** from the stack (echo and hi) and created a node with those as left and right
** child. The null node is then moved to the stack, followed my ls. > is a
** unary operation, so it makes a node with only ls, and the > node is moved
** to stack. At this point, we have > and (null) in the stack. Last we have
** ; operator, that takes > and (null) as its left and right node. This tree
** is then returned.
*/

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

t_node	*create_opnode(t_token *tkn, t_node **node_stack, int *i)
{
	t_node	*new_node;

	new_node = init_node();
	new_node->command = ft_strdup(tkn->value);
	new_node->operation = tkn->maintoken;
	new_node->subtokens = tkn->subtokens;
	if (is_unaryop(tkn))
		new_node->right = NULL;
	else if (*i > 1)
	{
		*i = *i - 1;
		new_node->right = node_stack[*i];
		node_stack[*i]->parent = new_node;
		node_stack[*i] = NULL;
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
		ft_printf((node_stack[0])->command);
		ft_printf((node_stack[1])->command);
		ft_printf_fd(2, "syntax error");
		return (NULL);
	}
	return (node_stack[0]);
}
