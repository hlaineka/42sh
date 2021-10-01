/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 10:34:59 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 18:35:14 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	sig_handler_input(int signo)
{
	t_input	*input;
	t_term	*term;
	int		col;
	int		row;

	(void)signo;
	col = g_input->prompt_col - 1;
	row = g_input->prompt_row - 1;
	term = g_term;
	input = g_input;
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	ft_putstr_input(input->ls, input, term);
	ft_putrstr_input(input->rrs, input, term);
	input->ls[0] = '\0';
	input->rrs[0] = '\0';
	input->hist_i = 0;
	*input->quote = PROMPT_NORMAL;
	ft_putstr_fd("\n\r", STDOUT_FILENO);
	ft_memdel((void **)input->ret_str);
	ft_memdel((void **)input->input_temp);
	if (input->input_mode == HEREDOC_MODE)
		init_input_tty(input, PROMPT_HEREDOC);
	else
		init_input_tty(input, PROMPT_START);
}

void	sig_ttou_input(int signo)
{
	ft_printf("INPUT: SIGTTOU signal %d\n", signo);
}

void	set_signal_input(void)
{
	if ((signal(SIGINT, sig_handler_input) == SIG_ERR)
		|| (signal(SIGTERM, sig_handler_input) == SIG_ERR)
		|| (signal(SIGQUIT, sig_handler_input) == SIG_ERR)
		|| (signal(SIGHUP, sig_handler_input) == SIG_ERR)
		|| (signal(SIGXCPU, sig_handler_input) == SIG_ERR)
		|| (signal(SIGTTOU, sig_ttou_input) == SIG_ERR))
		ft_exit(0);
}
