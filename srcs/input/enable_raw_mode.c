/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_raw_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/17 09:18:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void		ft_cfmakeraw(t_termios *termios_p)
{
	termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP \
							| INLCR | IGNCR | ICRNL | IXON);
	termios_p->c_oflag &= ~OPOST;
	termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	termios_p->c_cflag &= ~(CSIZE | PARENB);
	termios_p->c_cflag |= CS8;
}

void			enable_raw_mode(t_term *term)
{
	t_termios	raw;

	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		err_fatal(ERR_MESSAGE, "tcgetattr", term);
	term->orig_termios = raw;
	ft_cfmakeraw(&raw);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1) //TCSANOW or TCSAFLUSH
		err_fatal(ERR_MESSAGE, "tcsetattr", term);
//	tputs(prog->ti_string, 1, ft_putc);
//	tputs(prog->vi_string, 1, ft_putc);
}
