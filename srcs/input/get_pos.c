/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:24:01 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 10:42:43 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static int	get_cur_x(int *x, char *buf, int *i)
{
	int		pow;

	pow = 1;
	*x = 0;
	*i = *i - 2;
	while (buf[*i] != ';' && *i > 0)
	{
		*x = *x + (buf[*i] - '0') * pow;
		pow *= 10;
		*i = *i - 1;
	}
	return (0);
}

static int	get_cur_y(int *y, char *buf, int *i)
{
	int		pow;

	pow = 1;
	*y = 0;
	*i = *i - 1;
	while (buf[*i] != '[' && *i > 0)
	{
		*y = *y + (buf[*i] - '0') * pow;
		pow *= 10;
		*i = *i - 1;
	}
	return (0);
}

int			get_pos(int *y, int *x)
{
	char	buf[30];
	int		i;
	char	ch;

	i = 0;
	ch = 0;
	ft_bzero(buf, sizeof(char) * 30);
	write(1, "\033[6n", 4);
	while (ch != 'R' || i > 30)
	{
		if (!(read(0, &ch, 1)))
		{
			ft_printf_fd(2, "cursor position reading failed.\n\r"); //change
			return (-1);
		}
		buf[i++] = ch;
	}
	if (i < 2)
	{
		ft_printf("i < 2\n\r");
		return (1);
	}
	get_cur_x(x, buf, &i);
	get_cur_y(y, buf, &i);
	return (0);
}
