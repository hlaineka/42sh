/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_raw_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:31:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/25 18:19:03 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void		disable_raw_mode_continue(t_term *term)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->orig_termios) == -1)
		err_quit(ERR_MESSAGE, "tcsetattr"); // or other error?
}

void		disable_raw_mode(t_term *term)
{
	tputs(term->te_string, 1, ft_putc);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->orig_termios) == -1)
		err_quit(ERR_MESSAGE, "tcsetattr"); // or other error?
}

int			disable_rawmode(void)
{
	tputs(g_term->te_string, 1, ft_putc);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_term->orig_termios) == -1)
		die("tcsetattr");
	return (1);
}
