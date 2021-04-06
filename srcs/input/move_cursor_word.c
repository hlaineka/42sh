/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:51:38 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 11:59:37 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	print_and_pos(t_input *input, t_term *term)
{
	int		x;
	int		y;

	x = input->prompt_col - 1;
	y = input->prompt_row - 1;
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
	x = input->cursor_col - 1;
	y = input->cursor_row - 1;
	ft_putrstr_input(input->rrs, input, term);
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc);
}

void	move_prev_word(t_input *input, t_term *term)
{
	int		len;
	int		i;

	len = ft_strlen(input->ls);
	if (len < 1)
		return ;
	i = len - 1;
	while (i >= 0 && input->ls[i]
		&& (input->ls[i] == ' ' || input->ls[i] == 13))
		i--;
	while (i >= 0 && input->ls[i]
		&& (input->ls[i] != ' ' && input->ls[i] != 13))
		i--;
	i = len - i - 1;
	move_nchars_from_s1_to_s2(input->ls, input->rrs, input->ls_size, i);
	print_and_pos(input, term);
}

void	move_next_word(t_input *input, t_term *term)
{
	int		len;
	int		i;

	len = ft_strlen(input->rrs);
	if (len < 1)
		return ;
	i = len - 1;
	while (i > 0 && input->rrs[i] && input->rrs[i] != ' '
		&& input->rrs[i] != 13)
		i--;
	while (i > 0 && input->rrs[i] && (input->rrs[i] == ' '
			|| input->rrs[i] == 13))
		i--;
	i = len - i - 1;
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, i);
	print_and_pos(input, term);
}
