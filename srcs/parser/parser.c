/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:37:51 by helvi             #+#    #+#             */
/*   Updated: 2021/07/25 12:29:49 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static void	debug_print_right(t_node *node, char *prefix)
{
	char	*temp;

	temp = NULL;
	if (prefix == NULL && node->left)
		temp = ft_strdup("|");
	else if (prefix == NULL)
		temp = ft_strdup("");
	else if (node->right->left || node->right->right)
		temp = ft_strjoin(prefix, "  |");
	else
		temp = ft_strjoin(prefix, "  ");
	debug_print_tree(node->right, temp, 2);
	ft_free(temp);
}

static void	debug_print_left(t_node *node, char *prefix)
{
	char	*temp;

	temp = NULL;
	if (prefix == NULL)
		temp = ft_strdup("");
	else
		temp = ft_strjoin(prefix, "  ");
	debug_print_tree(node->left, temp, 1);
	ft_free(temp);
}

void	debug_print_tree(t_node *node, char *prefix, int left_right)
{
	if (!node)
		return ;
	if (prefix != NULL)
	{
		ft_printf_fd(STDOUT_FILENO, prefix);
		if (ft_strlen(prefix) > 0 && prefix[ft_strlen(prefix) - 1] == '|')
			ft_printf_fd(STDOUT_FILENO, "--");
		else
			ft_printf_fd(STDOUT_FILENO, "|--");
	}
	if (left_right == 1)
		ft_printf_fd(STDOUT_FILENO, "left ");
	if (left_right == 2)
		ft_printf_fd(STDOUT_FILENO, "right ");
	ft_printf_fd(STDOUT_FILENO, "[%s]\n", node->command);
	if (node->right)
		debug_print_right(node, prefix);
	if (node->left)
		debug_print_left(node, prefix);
}

t_node	*parser(char *input, t_term *term)
{
	t_token	*tokens;
	t_node	*root;

	tokens = lexer(input, term, 1);
	root = ast_creator(tokens, term);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tree(root, NULL, 0);
	free_tokens(tokens);
	return (root);
}
