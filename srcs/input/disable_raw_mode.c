/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_raw_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:31:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/11 10:41:50 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		disable_raw_mode(t_term *term)
{
	tputs(term->te_string, 1, ft_putc);
	if (tcsetattr(STDIN_FILENO, SCSAFLUSH, &term->orig_termios) == -1)
		exit(1); // ft_errror fun here!
	return (1); // return int or void?
}
