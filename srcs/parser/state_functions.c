/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:36:22 by helvi             #+#    #+#             */
/*   Updated: 2021/03/23 19:35:56 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_node		*add_node(t_node *current_node, t_token *current_token, int state)
{
	if (!current_node->left)
	{
		ft_printf("in left. ");
		current_node->left = init_node();
		current_node->command = ft_strdup(current_token->value);
		current_node->left->state = state;
		current_node->left->parent = current_node;
		return (current_node->left);
	}
	else if (!current_node->right)
	{
		ft_printf("in right. ");
		current_node->right = init_node();
		current_node->command = ft_strdup(current_token->value);
		current_node->right->state = state;
		current_node->right->parent = current_node;
		return (current_node->right);
	}
	else
	{
		ft_printf_fd(2, "problem with adding nodes, left and right taken.");
		return (NULL);
	}
}

t_node		*complete_word(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable = add_node(current_node, current_token, command)))
		return (NULL);
	ft_printf("in complete_word, %s, %s, %i .\n", current_node->command, current_token->value, returnable->state);
	return (returnable);
}

t_node		*command_word(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable = add_node(current_node, current_token, cmd_suffix)))
		return (NULL);
	ft_printf("in command_word, %s, %s.\n", current_node->command, current_token->value);
	return (returnable);
}

t_node		*command_operator(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable =  add_node(current_node, current_token, complete_command)))
		return (NULL);
	ft_printf("in command_operator, %s, %s.\n", current_node->command, current_token->value);
	return (returnable);
}

t_node		*command_redircetion(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable = add_node(current_node, current_token, redirection)))
		return (NULL);
	ft_printf("in command_redircetion, %s, %s.\n", current_node->command, current_token->value);
	return (returnable);
}

t_node		*cmd_suffix_word(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable = add_node(current_node, current_token, command)))
		return (NULL);
	ft_printf("in cmd_suffix_word, %s, %s.\n", current_node->command, current_token->value);
	return (returnable);
}

t_node		*cmd_suffix_operator(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable = add_node(current_node, current_token, complete_command)))
		return (NULL);
	ft_printf("in cmd_suffix_operator, %s, %s.\n", current_node->command, current_token->value);
	return (returnable);
}

t_node		*cmd_suffix_redirection(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable = add_node(current_node, current_token, redirection)))
		return (NULL);
	ft_printf("in cmd_suffix_redirection, %s, %s.\n", current_node->command, current_token->value);
	return (returnable);
}

t_node		*redirection_word(t_node *current_node, t_token *current_token)
{
	t_node	*returnable;

	returnable = NULL;
	if (NULL == (returnable = add_node(current_node, current_token, complete_command)))
		return (NULL);
	ft_printf("in redirection_word, %s, %s.\n", current_node->command, current_token->value);
	return (returnable);
}
