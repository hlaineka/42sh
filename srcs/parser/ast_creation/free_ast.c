/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:07:53 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/09 15:54:10 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

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