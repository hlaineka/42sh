/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:58:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/07 17:07:09 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "includes.h"

static const op_function g_op_functions[] =
{
	[tkn_token] = token_null,
	[tkn_word] = NULL,
	[tkn_operator] = NULL,
	[tkn_name] = NULL,
	[tkn_assignment_word] = NULL,
	[tkn_io_number] = NULL,
	[tkn_and] = NULL,
	[tkn_lpar] = NULL,
	[tkn_rpar] = NULL,
	[tkn_semi] = token_semi,
	[tkn_nl] = NULL,
	[tkn_pipe] = token_pipe,
	[tkn_less] = NULL,
	[tkn_great] = NULL,
	[tkn_and_if] = NULL,
	[tkn_or_if] = NULL,
	[tkn_dsemi] = NULL,
	[tkn_dless] = NULL,
	[tkn_dgreat] = NULL,
	[tkn_lessand] = NULL,
	[tkn_greatand] = NULL,
	[tkn_lessgreat] = NULL,
	[tkn_dlessdash] = NULL,
	[tkn_clobber] = NULL,
	[tkn_if] = NULL,
	[tkn_then] = NULL,
	[tkn_else] = NULL,
	[tkn_elif] = NULL,
	[tkn_fi] = NULL,
	[tkn_do] = NULL,
	[tkn_done] = NULL,
	[tkn_case] = NULL,
	[tkn_tesac] = NULL,
	[tkn_while] = NULL,
	[tkn_until] = NULL,
	[tkn_for] = NULL,
	[tkn_lbrace] = NULL,
	[tkn_rbrace] = NULL,
	[tkn_bang] = NULL,
	[tkn_in] = NULL,
	[tkn_eoi] = NULL,
	[tkn_eoi + 1] = NULL
};

t_job	*tree_traversal(t_node *current)
{
	t_job	*returnable;

	returnable = NULL;
	if (!current->left && !current->right && current->operation == tkn_word)
		return (token_null(returnable, current));
	if (g_op_functions[current->operation])
		returnable = g_op_functions[current->operation](returnable, current);
	return (returnable);
}