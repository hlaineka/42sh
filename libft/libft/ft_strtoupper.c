/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 22:32:00 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/06 16:22:51 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtoupper(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}