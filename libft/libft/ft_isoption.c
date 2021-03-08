/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoption.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:47:25 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/10 00:03:02 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isoption(char *str)
{
	if (!str || *str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalpha(*str))
			return (0);
		str++;
	}
	return (1);
}

int		ft_islongoption(char *str)
{
	if (!str || str[0] != '-' || str[1] != '-')
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalpha(*str))
			return (0);
		str++;
	}
	return (1);
}
