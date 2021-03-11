/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_raw_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:31:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/11 20:42:43 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void		disable_raw_mode(t_term *term)
{
	tputs(term->te_string, 1, ft_putc);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->orig_termios) == -1)
		err_quit(ERR_MESSAGE, "tcsetattr"); // or other error?
}
