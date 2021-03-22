/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_and_end_keypress.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:03:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 11:05:46 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void			home_keypress(t_input *input, t_term *term)
{
	int		ls_len;
	int		row;
	int		col;

	ls_len = ft_strlen(input->ls);
	row = input->prompt_row - 1;
	col = input->prompt_col - 1;
	move_nchars_from_s1_to_s2(input->ls, input->rrs, input->rrs_size, ls_len);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	get_pos(&input->cursor_row, &input->cursor_col);
}

void			end_keypress(t_input *input, t_term *term)
{
	int		ls_len;
	int		rrs_len;
	int		print_len;
	int		x;
	int		y;

	ls_len = ft_strlen(input->ls);
	rrs_len = ft_strlen(input->rrs);
	print_len = ls_len + rrs_len + input->prompt_length;
	y = (print_len / term->ncolumns) + (input->start_row - 1);
	x = (print_len % term->ncolumns) + (input->start_col - 1);
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, rrs_len);
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc);
	get_pos(&input->cursor_row, &input->cursor_col);
}
