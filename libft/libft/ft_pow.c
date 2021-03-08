/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 14:19:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/08 16:24:22 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_pow(double x, double y)
{
	double		ret;

	ret = 1;
	while (y > 0)
	{
		ret = ret * x;
		y--;
	}
	return (ret);
}
