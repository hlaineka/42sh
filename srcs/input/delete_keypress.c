/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:28:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 13:38:46 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	backspace_keypress(t_input *input, t_term *term)
{
	int		col;
	int		row;

	if (!input->ls[0])
		return ;
	move_cursor_left(&input->cursor_row, &input->cursor_col, term);
	col = input->cursor_col - 1;
	row = input->cursor_row - 1;
	input->ls[ft_strlen(input->ls) - 1] = '\0';
	ft_putrstr_input(input->rrs, input, term);
	tputs(term->dc_string, 1, ft_putc);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
}

void	delete_keypress(t_input *input, t_term *term)
{
	int		col;
	int		row;

	if (!input->rrs[0])
		return ;
	input->rrs[ft_strlen(input->rrs) - 1] = '\0';
	col = input->cursor_col - 1;
	row = input->cursor_row - 1;
	ft_putrstr_input(input->rrs, input, term);
	tputs(term->dc_string, 1, ft_putc);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
}
