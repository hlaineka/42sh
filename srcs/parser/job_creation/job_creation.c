/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:40:47 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/30 12:13:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "execution.h"
#include "includes.h"

int			init_func_pointers(op_function *op_funcs)
{
	op_funcs[tkn_token] = &null_token;
	//op_funcs[tkn_word] =
	//op_funcs[tkn_operator] =
	//op_funcs[tkn_name] =
	//op_funcs[tkn_assignment_word] =
	//op_funcs[tkn_io_number] =
	//op_funcs[tkn_and] =
	//op_funcs[tkn_lpar] =
	//op_funcs[tkn_rpar] =
	//op_funcs[tkn_semi] =
	//op_funcs[tkn_nl] =
	//op_funcs[tkn_pipe] =
	//op_funcs[tkn_less] =
	//op_funcs[tkn_great] =
	//op_funcs[tkn_and_if] =
	//op_funcs[tkn_or_if] =
	//op_funcs[tkn_dsemi] =
	//op_funcs[tkn_dless] =
	//op_funcs[tkn_dgreat] =
	//op_funcs[tkn_lessand] =
	//op_funcs[tkn_greatand] =
	//op_funcs[tkn_lessgreat] =
	//op_funcs[tkn_dlessdash] =
	//op_funcs[tkn_clobber] =
	//op_funcs[tkn_if] =
	//op_funcs[tkn_then] =
	//op_funcs[tkn_else] =
	//op_funcs[tkn_elif] =
	//op_funcs[tkn_fi] =
	//op_funcs[tkn_do] =
	//op_funcs[tkn_done] =
	//op_funcs[tkn_case] =
	//op_funcs[tkn_tesac] =
	//op_funcs[tkn_while] =
	//op_funcs[tkn_until] =
	//op_funcs[tkn_for] =
	//op_funcs[tkn_lbrace] =
	//op_funcs[tkn_rbrace] =
	//op_funcs[tkn_bang] =
	//op_funcs[tkn_in] =
	//op_funcs[tkn_eoi] =
	return (0);
}

t_job		*init_job(void)
{
	t_job		*returnable;
	t_process	*first_process;

	returnable = malloc(sizeof(t_job));
	first_process = malloc(sizeof(t_process));
	ft_bzero(returnable, sizeof(t_job));
	ft_bzero(first_process, sizeof(t_process));
	first_process->next = NULL;
	first_process->argv = malloc(ARGV_SIZE);
	ft_bzero(first_process->argv, ARGV_SIZE);
	returnable->next = NULL;
	returnable->command = NULL;
	returnable->first_process = first_process;
	return(returnable);
}

int			job_creation(t_node *root, bool debug)
{
	//t_job		*executable;
	//op_function	op_funcs[NUMBER_OF_TOKENS];

	//init_func_pointers(op_funcs);
	//executable = init_job();
	while (tokens && debug)
	{
		tokens = tokens->next;
	}
	return (0);
}
*/