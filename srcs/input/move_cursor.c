/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:20:06 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 10:20:46 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int				move_cursor_up(int *row, int *col, t_term *term)
{
	if (*row == 1)
		return (0);
	*row = *row - 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}

int				move_cursor_down(int *row, int *col, t_term *term)
{
	if (*row == (int)term->nrows)
		return (0);
	*row = *row + 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}

int				move_cursor_right(int *row, int *col, t_term *term)
{
	if (*col == (int)term->ncolumns)
	{
		*col = 1;
		*row = *row + 1;
	}
	else
		*col = *col + 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}

int				move_cursor_left(int *row, int *col, t_term *term)
{
	if (*col == 1)
	{
		*col = term->ncolumns;
		*row = *row - 1;
	}
	else
		*col = *col - 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}
