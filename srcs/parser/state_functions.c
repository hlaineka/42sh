/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:36:22 by helvi             #+#    #+#             */
/*   Updated: 2021/03/18 21:25:55 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		complete_word(t_node *current_node, t_token *current_token)
{
	current_node->command = ft_strdup(current_token->value);
	ft_printf("in complete_word, %s, %s.\n", current_node->command, current_token->value);
}

int		command_word(t_node *current_node, t_token *current_token)
{
	current_node->command = ft_strdup(current_token->value);
	ft_printf("in command_word, %s, %s.\n", current_node->command, current_token->value);
}