/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:34:07 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/31 10:20:25 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_node	*init_node(void)
{
	t_node	*returnable;

	returnable = malloc(sizeof(t_node));
	ft_bzero(returnable, sizeof(t_node));
	returnable->parent = NULL;
	returnable->left = NULL;
	returnable->right = NULL;
	returnable->command = NULL;
	returnable->full_command = NULL;
	return (returnable);
}

int	is_unaryop(t_token *tkn)
{
	if (tkn->maintoken == tkn_less || tkn->maintoken == tkn_great
		|| tkn->maintoken == tkn_dless || tkn->maintoken == tkn_dgreat
		|| tkn->maintoken == tkn_lessand || tkn->maintoken == tkn_greatand
		|| tkn->maintoken == tkn_lessgreat || tkn->maintoken == tkn_clobber
		|| tkn->maintoken == tkn_lpar || tkn->maintoken == tkn_rpar
		|| tkn->maintoken == tkn_dollarlpar || tkn->maintoken == tkn_lbrace
		|| tkn->maintoken == tkn_rbrace)
		return (1);
	return (0);
}

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->command)
			ft_free(node->command);
		if (node->subtokens)
			free_tokens(node->subtokens);
		if (node->full_command)
			ft_free(node->full_command);
		ft_free(node);
	}
}

void	free_ast(t_node *root)
{
	if (root && root->right)
		free_ast(root->right);
	if (root && root->left)
		free_ast(root->left);
	if (root)
		free_node(root);
}

void	free_nodestack(t_node *stack[])
{
	int	i;

	i = 0;
	while (stack[i] && i < NODE_STACK_SIZE)
	{
		free_ast(stack[i]);
		i++;
	}
}
