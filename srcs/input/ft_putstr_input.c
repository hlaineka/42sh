/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:09:24 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 11:13:10 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void			ft_putchar_input(char c, t_input *input, t_term *term)
{
	int		x;
	int		y;

	x = input->cursor_col - 1;
	y = input->cursor_row - 1;
	x += write(STDOUT_FILENO, &c, 1);
	if (x == (int)term->ncolumns)
	{
		write(STDOUT_FILENO, "\n\r", 2);
		x = 0;
		y++;
	}
}

void			ft_putstr_input(char *str, t_input *input, t_term *term)
{
	int		x;
	int		y;
	int		i;

	get_pos(&input->cursor_row, &input->cursor_col);
	x = input->cursor_col - 1;
	y = input->cursor_row;
	i = 0;
	while (str[i])
	{
		x += write(STDOUT_FILENO, &str[i], 1);
		if (str[i] == '\n') // dont do like this!!!!
		{
			write(STDOUT_FILENO, "\r", 1);
			x = 0;
		}
		i++;
		if (x == (int)term->ncolumns)
		{
			write(STDOUT_FILENO, "\n\r", 2);
			if (y == (int)term->nrows)
			{
				input->start_row -= 1;
				input->prompt_row -= 1;
			}
			else
				y++;
			x = 0;
		}
	}
}

void			ft_putrstr_input(char *str, t_input *input, t_term *term)
{
	int		x;
	int		y;
	int		len;

	get_pos(&input->cursor_row, &input->cursor_col);
	x = input->cursor_col - 1;
	y = input->cursor_row;
	len = ft_strlen(str);
	while (len-- > 0)
	{
		x += write(STDOUT_FILENO, &str[len], 1);
		if (x == (int)term->ncolumns)
		{
			write(STDOUT_FILENO, "\n\r", 2);
			if (y == (int)term->nrows)
			{
				input->start_row -= 1;
				input->prompt_row -= 1;
			}
			else
				y++;
			x = 0;
		}
	}
}
