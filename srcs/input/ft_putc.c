/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:12:20 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/12 19:01:26 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int			ft_putc(int c)
{
//	write(g_term->fd_stdout, &c, 1);
	return (write(STDIN_FILENO, &c, 1));
//	return (1);
}
