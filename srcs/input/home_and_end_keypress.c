/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_and_end_keypress.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:03:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 11:36:41 by hhuhtane         ###   ########.fr       */
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
	int		rrs_len;
	int		row;
	int		col;

	rrs_len = ft_strlen(input->rrs);
	row = input->prompt_row - 1;
	col = input->prompt_col - 1;
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, rrs_len);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
	return (0);
}
