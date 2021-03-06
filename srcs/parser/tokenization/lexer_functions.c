/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:26:22 by hlaineka          #+#    #+#             */
/*   Updated: 2021/10/03 21:50:44 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "execution.h"

static t_token	*run_semicolon_command(t_token **command_first, t_term *term,
	t_token **temp)
{
	t_node	*root;
	t_token	*returnable;

	returnable = (*temp)->next;
	returnable->prev = NULL;
	(*temp)->next = NULL;
	if ((*temp)->prev)
	{
		(*temp)->prev->next = NULL;
		free_token(temp);
	}
	*temp = advanced_tokenization(*command_first, term, 1);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tokens(*command_first, "advanced_tokenization in semi");
	root = ast_creator(*temp, term);
	execute(root, term);
	*command_first = NULL;
	return (returnable);
}

static void	callback_init(t_token **returnable, t_token **temp)
{
	if ((*temp)->next)
	{
		*returnable = (*temp)->next;
		(*returnable)->prev = NULL;
		(*temp)->next = NULL;
	}
	else
		*returnable = NULL;
	if ((*temp)->prev)
	{
		(*temp)->prev->next = NULL;
		free_token(temp);
	}
}

static t_token	*run_and_if_command(t_token **command_first, t_term *term,
	t_token **temp)
{
	t_node	*root;
	t_token	*returnable;
	t_token	*temp2;

	callback_init(&returnable, temp);
	temp2 = advanced_tokenization(*command_first, term, 1);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tokens(*command_first, "advanced_tokenization in semi");
	root = ast_creator(temp2, term);
	execute(root, term);
	if (term->jobs->next->first_process->status != 0)
	{
		*temp = delete_until(returnable, term);
		returnable = *temp;
	}
	*command_first = NULL;
	return (returnable);
}

static t_token	*run_or_if_command(t_token **command_first, t_term *term,
	t_token **temp)
{
	t_node	*root;
	t_token	*returnable;
	t_token	*temp2;
	t_token	*temp3;

	callback_init(&returnable, temp);
	temp3 = *command_first;
	temp2 = advanced_tokenization(*command_first, term, 1);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tokens(*command_first, "advanced_tokenization in semi");
	root = ast_creator(temp2, term);
	execute(root, term);
	if (term->jobs->next->first_process->status == 0)
	{
		*temp = delete_until(returnable, term);
		returnable = *temp;
	}
	*command_first = NULL;
	return (returnable);
}

/*
static void	callback_and_set(t_token **temp, t_token **command_first,
	t_term *term, t_token *(*callback)(t_token **, t_term *, t_token **))
{
	*command_first = callback(command_first, term, temp);
	*temp = *command_first;
}
*/

t_token	*check_semicolon(t_token *first, t_term *term)
{
	t_token	*temp;
	t_token	*cmd_first;

	temp = first;
	cmd_first = NULL;
	while (temp)
	{
		if (!cmd_first)
			cmd_first = temp;
		if (temp->maintoken == tkn_semi && temp->next)
			lexer_callback(&temp, &cmd_first, term, &run_semicolon_command);
		else if (temp->maintoken == tkn_semi && !temp->next && temp->prev)
		{
			temp->prev->next = NULL;
			free_token(&temp);
		}
		else if (temp->maintoken == tkn_and_if)
			lexer_callback(&temp, &cmd_first, term, &run_and_if_command);
		else if (temp->maintoken == tkn_or_if)
			lexer_callback(&temp, &cmd_first, term, &run_or_if_command);
		else
			temp = temp->next;
	}
	return (cmd_first);
}
