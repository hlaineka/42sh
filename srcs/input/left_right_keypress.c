/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right_keypress.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:15:25 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/07 17:05:33 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	left_keypress(t_input *input, t_term *term)
{
	int		row;
	int		col;

	if (!input->ls[0])
		return ;
	if (input->ls[ft_strlen(input->ls) - 1] == 13
		|| input->ls[ft_strlen(input->ls) - 1] == 9
		|| input->ls[ft_strlen(input->ls) - 1] == 10 )
	{
		clear_screen_after_prompt(input, term);
		move_char_from_s1_to_s2(input->ls, input->rrs, input->rrs_size);
		ft_putstr_input(input->ls, input, term);
		get_pos(&input->cursor_row, &input->cursor_col);
		ft_putrstr_input(input->rrs, input, term);
		col = input->cursor_col - 1;
		row = input->cursor_row - 1;
		tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	}
	else
	{
		move_char_from_s1_to_s2(input->ls, input->rrs, input->rrs_size);
		move_cursor_left(&input->cursor_row, &input->cursor_col, term);
	}
	get_pos(&input->cursor_row, &input->cursor_col);
}

void	right_keypress(t_input *input, t_term *term)
{
	int		row;
	int		col;

	if (!input->rrs[0])
		return ;
	move_char_from_s1_to_s2(input->rrs, input->ls, input->rrs_size);
	if (input->ls[ft_strlen(input->ls) - 1] == 13)
		tputs(tgoto(term->cm_string, 0, input->cursor_row), 1, ft_putc);
	else if (input->ls[ft_strlen(input->ls) - 1] == 9
		|| input->ls[ft_strlen(input->ls) - 1] == 10)
	{
		col = input->prompt_col - 1;
		row = input->prompt_row - 1;
		tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
		ft_putstr_input(input->ls, input, term);
		get_pos(&input->cursor_row, &input->cursor_col);
		ft_putrstr_input(input->rrs, input, term);
		col = input->cursor_col - 1;
		row = input->cursor_row - 1;
		tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	}
	else
		move_cursor_right(&input->cursor_row, &input->cursor_col, term);
	get_pos(&input->cursor_row, &input->cursor_col);
}
