/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frexp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:31:36 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/09/01 09:28:02 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_frexp(double x, int *exp)
{
	t_doubleu		split;

	split.ld = x;
	*exp = split.bits.exp - 1023;
	split.bits.exp = 1023;
	return (split.ld);
}
