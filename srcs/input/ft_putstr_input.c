/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:09:24 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/23 17:13:25 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void		print_newline(int *x, int *y, t_input *input, t_term *term)
{
	write(STDOUT_FILENO, "\n\r", 2);
	tputs(term->ce_string, 1, ft_putc);
	*x = 0;
	if (*y == (int)term->nrows)
	{
		input->start_row -= 1;
		input->prompt_row -= 1;
	}
	else
		*y = *y + 1;
}

static void		ft_putchar_input(char c, int *x, int *y, t_term *term)
{
	t_input	*input;

	input = term->input;
	if (c == 13 || c == '\n')
		print_newline(x, y, input, term);
	else
		*x += write(STDOUT_FILENO, &c, 1);
	if (*x == (int)term->ncolumns)
		print_newline(x, y, input, term);
}

void			ft_putstr_input(char *str, t_input *input, t_term *term)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	get_pos(&input->cursor_row, &input->cursor_col);
	x = input->cursor_col - 1;
	y = input->cursor_row;
	tputs(term->ce_string, 1, ft_putc);
	while (str[i])
	{
		ft_putchar_input(str[i], &x, &y, term);
		i++;
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
		ft_putchar_input(str[len], &x, &y, term);
}
