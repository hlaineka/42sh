/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:34:07 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/28 16:04:05 by hlaineka         ###   ########.fr       */
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
	return (returnable);
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

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->command)
			ft_free(node->command);
		if (node->subtokens)
			free_tokens(node->subtokens);
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
