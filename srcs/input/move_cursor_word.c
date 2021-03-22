/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:51:38 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 11:52:10 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void			move_prev_word(t_input *input, t_term *term)
{
	int		len;
	int		i;
	int		x;
	int		y;

	len = ft_strlen(input->ls);
	if (len < 1)
		return ;
	i = len - 1;
	while (i >= 0 && input->ls[i] && input->ls[i] == ' ')
		i--;
	while (i >= 0 && input->ls[i] && input->ls[i] != ' ')
		i--;
	i = len - i - 1;
	move_nchars_from_s1_to_s2(input->ls, input->rrs, input->ls_size, i);
	len = ft_strlen(input->ls) + input->prompt_length;
	y = input->start_row + (len / term->ncolumns) - 1;
	x = input->start_col + (len % term->ncolumns) - 1;
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc);
	get_pos(&input->cursor_row, &input->cursor_col);
}

void			move_next_word(t_input *input, t_term *term)
{
	int		len;
	int		i;
	int		x;
	int		y;

	len = ft_strlen(input->rrs);
	if (len < 1)
		return ;
	i = len - 1;
	while (i > 0 && input->rrs[i] && input->rrs[i] != ' ')
		i--;
	while (i > 0 && input->rrs[i] && input->rrs[i] == ' ')
		i--;
	i = len - i - 1;
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, i);
	len = ft_strlen(input->ls) + input->prompt_length;
	y = input->start_row + (len / term->ncolumns) - 1;
	x = input->start_col + (len % term->ncolumns) - 1;
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc);
	get_pos(&input->cursor_row, &input->cursor_col);
}
