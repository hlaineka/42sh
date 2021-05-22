/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_raw_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/21 21:04:08 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	ft_cfmakeraw(struct termios *termios_p)
{
	termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	termios_p->c_oflag &= ~OPOST;
	termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	termios_p->c_cflag &= ~(CSIZE | PARENB);
	termios_p->c_cflag |= CS8;
}

void	get_termios_modes(t_term *term)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		err_fatal(ERR_MESSAGE, "tcgetattr", term);
	term->orig_termios = raw;
	ft_cfmakeraw(&raw);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	term->raw = raw;
}

/*
** CHECK:
** tcsetattr TCSANOW or TCSAFLUSH?
*/
void	enable_raw_mode(t_term *term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term->raw) == -1)
		err_fatal(ERR_MESSAGE, "tcsetattr", term);
}
