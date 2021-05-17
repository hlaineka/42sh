/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_raw_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:31:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/17 11:49:48 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "init.h"

void	disable_raw_mode_continue(t_term *term)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->orig_termios) == -1)
		err_quit(ERR_MESSAGE, "tcsetattr");
}

void	disable_raw_mode(t_term *term)
{
	tputs(term->te_string, 1, ft_putc);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->orig_termios) == -1)
		err_quit(ERR_MESSAGE, "tcsetattr");
}

int	disable_rawmode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_term->orig_termios) == -1)
		die("tcsetattr");
	return (1);
}
