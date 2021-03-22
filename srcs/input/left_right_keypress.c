/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right_keypress.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:15:25 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 13:22:38 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	left_keypress(t_input *input, t_term *term)
{
	if (!input->ls[0])
		return ;
	move_cursor_left(&input->cursor_row, &input->cursor_col, term);
	move_char_from_s1_to_s2(input->ls, input->rrs, input->rrs_size);
}

void	right_keypress(t_input *input, t_term *term)
{
	if (!input->rrs[0])
		return ;
	move_cursor_right(&input->cursor_row, &input->cursor_col, term);
	move_char_from_s1_to_s2(input->rrs, input->ls, input->rrs_size);
}
