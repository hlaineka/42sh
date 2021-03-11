/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.f...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:42:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/02/24 17:00:35 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_nbr_base(char c, int base)
{
	int		max_nb;

	if (base <= 10)
		max_nb = base + '0';
	else
		max_nb = base - 10 + 'a';
	if (c >= '0' && c <= '9' && c < max_nb)
		return (c - '0');
	else if (c >= 'a' && c < max_nb)
		return (10 + c - 'a');
	else
		return (-1);
}

int				ft_atoi_base(const char *str, int base)
{
	int					sign;
	int					i;
	int					num;
	size_t				result;

	i = 0;
	num = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (num = ft_get_nbr_base(ft_tolower(str[i]), base)))
	{
		result = (result * base) + num;
		i++;
	}
	return (sign * (int)result);
}
