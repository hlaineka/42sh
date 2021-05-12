/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_rows_starting_y.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 11:38:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/07 09:32:07 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	clear_rows_starting_y(int y, t_term *term)
{
	tputs(tgoto(term->cm_string, 0, y), 1, ft_putc);
	tputs(term->cd_string, 1, ft_putc);
}

void	clear_screen_after_prompt(t_input *input, t_term *term)
{
	int		col;
	int		row;

	col = input->prompt_col - 1;
	row = input->prompt_row - 1;
	if (row + 1 < ((int)term->nrows))
	{
		tputs(tgoto(term->cm_string, 0, row + 1), 1, ft_putc);
		tputs(term->cd_string, 1, ft_putc);
	}
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	tputs(term->ce_string, 1, ft_putc);
}
