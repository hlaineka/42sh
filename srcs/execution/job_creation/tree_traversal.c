/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:58:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/12 10:42:22 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "includes.h"

/*
** The tree traversal checks the current operator in the tree and calls the
** function assigned to that operator from static const array of function
** pointers. If the function is not found, NULL pointer is returned. All the
** functions are named token_operatorname(). 
*/

static const t_op_function	g_op_functions[] = {
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
	[tkn_less] = token_less,
	[tkn_great] = token_great,
	[tkn_and_if] = token_and_if,
	[tkn_or_if] = token_or_if,
	[tkn_dsemi] = NULL,
	[tkn_dless] = token_dless,
	[tkn_dgreat] = token_dgreat,
	[tkn_lessand] = token_lessand,
	[tkn_greatand] = token_greatand,
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
	[tkn_redirop] = NULL,
	[tkn_syntax_error] = NULL,
	[tkn_dash] = NULL,
	[tkn_eoi] = NULL,
	[tkn_eoi + 1] = NULL
};

t_job	*tree_traversal(t_job *job, t_node *current, t_term *term)
{
	t_job	*returnable;

	returnable = NULL;
	if (!current->left && !current->right && current->operation == tkn_word)
		return (token_null(job, term, current));
	if (g_op_functions[current->operation])
		returnable = g_op_functions[current->operation](job, term, current);
	return (returnable);
}
