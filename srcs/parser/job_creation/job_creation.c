/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:40:47 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/06 16:38:54 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "includes.h"

int	init_func_pointers(t_job *(**op_functions)(t_job *job, t_node *current))
{
	op_functions[tkn_token] = null_token;
	op_functions[tkn_word] = NULL;
	op_functions[tkn_operator] = NULL;
	op_functions[tkn_name] = NULL;
	op_functions[tkn_assignment_word] = NULL;
	op_functions[tkn_io_number] = NULL;
	op_functions[tkn_and] = NULL;
	op_functions[tkn_lpar] = NULL;
	op_functions[tkn_rpar] = NULL;
	op_functions[tkn_semi] = NULL;
	op_functions[tkn_nl] = NULL;
	op_functions[tkn_pipe] = NULL;
	op_functions[tkn_less] = NULL;
	op_functions[tkn_great] = NULL;
	op_functions[tkn_and_if] = NULL;
	op_functions[tkn_or_if] = NULL;
	op_functions[tkn_dsemi] = NULL;
	op_functions[tkn_dless] = NULL;
	op_functions[tkn_dgreat] = NULL;
	op_functions[tkn_lessand] = NULL;
	op_functions[tkn_greatand] = NULL;
	op_functions[tkn_lessgreat] = NULL;
	op_functions[tkn_dlessdash] = NULL;
	op_functions[tkn_clobber] = NULL;
	op_functions[tkn_if] = NULL;
	op_functions[tkn_then] = NULL;
	op_functions[tkn_else] = NULL;
	op_functions[tkn_elif] = NULL;
	op_functions[tkn_fi] = NULL;
	op_functions[tkn_do] = NULL;
	op_functions[tkn_done] = NULL;
	op_functions[tkn_case] = NULL;
	op_functions[tkn_tesac] = NULL;
	op_functions[tkn_while] = NULL;
	op_functions[tkn_until] = NULL;
	op_functions[tkn_for] = NULL;
	op_functions[tkn_lbrace] = NULL;
	op_functions[tkn_rbrace] = NULL;
	op_functions[tkn_bang] = NULL;
	op_functions[tkn_in] = NULL;
	op_functions[tkn_eoi] = NULL;
	return (0);
}

static void	debug_printing(t_job *next_job)
{
	int	i;

	i = 0;
	ft_printf("argv of the first process: ");
	if (next_job)
	{
		while (next_job->first_process->argv[i])
		{
			ft_printf("%s, ", next_job->first_process->argv[i]);
			i++;
		}
	}
	ft_printf("\n");
}

t_job	*job_creation(t_node *root, bool debug)
{
	t_job	*returnable;
	t_job	*(*op_functions[tkn_eoi + 1])(t_job *job, t_node *current);

	init_func_pointers(op_functions);
	returnable = init_job();
	returnable = tree_traversal(root, op_functions, returnable);
	if (returnable == NULL)
		ft_printf_fd(2, "syntax_error\n");
	if (debug)
		debug_printing(returnable);
	return (returnable);
}
