/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_and_end_keypress.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:03:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/15 14:40:47 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	home_keypress(t_input *input, t_term *term)
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
	return (0);
}

int	end_keypress(t_input *input, t_term *term)
{
//	int		ls_len;
	int		rrs_len;
	int		row;
	int		col;

/*
	int		print_len;
	int		x;
	int		y;

	if (ft_strchr(input->ls, 13) || ft_strchr(input->rrs, 13))
	{
		x = input->prompt_col - 1;
		y = input->prompt_row - 1;
		tputs(tgoto(term->cm_string, x, y), 1, ft_putc);
		ft_putstr_input(input->ls, input, term);
		ft_putrstr_input(input->rrs, input, term);
		get_pos(&input->cursor_row, &input->cursor_col);
		return (0);
	}
	ls_len = ft_strlen(input->ls);
	rrs_len = ft_strlen(input->rrs);
	print_len = ls_len + rrs_len + input->prompt_length;
	y = (print_len / term->ncolumns) + (input->start_row - 1);
	x = (print_len % term->ncolumns) + (input->start_col - 1);
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, rrs_len);
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc);
	get_pos(&input->cursor_row, &input->cursor_col);
	return (0);
*/

	rrs_len = ft_strlen(input->rrs);
	row = input->prompt_row - 1;
	col = input->prompt_col - 1;
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, rrs_len);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
	return (0);
}
