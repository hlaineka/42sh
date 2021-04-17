/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 10:34:59 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/17 10:47:09 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	sig_handler_input(int signo)
{
	t_input	*input;
	t_term	*term;
	int		col;
	int		row;

	(void)signo; // check if or something
	col = g_input->prompt_col - 1;
	row = g_input->prompt_row - 1;
	term = g_term;
	input = g_input;
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	ft_putstr_input(input->ls, input, term);
	ft_putrstr_input(input->rrs, input, term);
	input->ls[0] = '\0';
	input->rrs[0] = '\0';
	*input->quote = PROMPT_NORMAL;
	ft_putstr_fd("\n\r", STDOUT_FILENO);
	ft_memdel((void**)input->ret_str);
	*input->input_temp = NULL;
// is quote on?
	init_input_tty(input, PROMPT_START);
}
