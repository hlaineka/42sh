/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:12:20 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/06/12 19:02:52 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_putc(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}
