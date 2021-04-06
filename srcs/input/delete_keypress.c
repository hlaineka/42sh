/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:28:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/25 20:12:59 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	print_clean_pos(t_input *input, t_term *term)
{
	int		col;
	int		row;

	col = input->prompt_col - 1;
	row = input->prompt_row - 1;
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	ft_putstr_input("\n", input, term);
	tputs(term->cd_string, 1, ft_putc);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
	col = input->cursor_col - 1;
	row = input->cursor_row - 1;
	ft_putrstr_input(input->rrs, input, term);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
}

void	backspace_keypress(t_input *input, t_term *term)
{
	int		col;
	int		row;

	if (!input->ls[0])
		return ;
	if (ft_strchr(input->ls, 13) || ft_strchr(input->rrs, 13))
	{
		input->ls[ft_strlen(input->ls) - 1] = '\0';
		print_clean_pos(input, term);
	}
	else
	{
		move_cursor_left(&input->cursor_row, &input->cursor_col, term);
		col = input->cursor_col - 1;
		row = input->cursor_row - 1;
		input->ls[ft_strlen(input->ls) - 1] = '\0';
		ft_putrstr_input(input->rrs, input, term);
		tputs(term->dc_string, 1, ft_putc);
		tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	}
}

void	delete_keypress(t_input *input, t_term *term)
{
	int		col;
	int		row;
	int		last;

	if (!input->rrs[0])
		return ;
	last = ft_strlen(input->rrs) - 1;
	if (ft_strchr(input->ls, 13) || ft_strchr(input->rrs, 13))
	{
		input->rrs[last] = '\0';
		print_clean_pos(input, term);
	}
	else
	{
		input->rrs[ft_strlen(input->rrs) - 1] = '\0';
		col = input->cursor_col - 1;
		row = input->cursor_row - 1;
		ft_putrstr_input(input->rrs, input, term);
		tputs(term->dc_string, 1, ft_putc);
		tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	}
}
