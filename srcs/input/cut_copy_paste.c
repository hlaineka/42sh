/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 19:10:53 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/07 09:25:21 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	copy_input_to_clipboard(t_input *input, t_term *term)
{
	char	*clipboard;

	(void)term;
	clipboard = ft_memalloc(sizeof(char) * (ft_strlen(input->ls)
				+ ft_strlen(input->rrs) + 1));
	if (!clipboard)
		return ;
	ft_strcpy(clipboard, input->ls);
	ft_strcpy(clipboard, input->ls);
	ft_strrcat(clipboard, input->rrs);
	free(input->clipboard);
	input->clipboard = clipboard;
}

void	paste_clipboard_to_input(t_input *input, t_term *term)
{
	int		col;
	int		row;
	size_t	len;

	col = input->prompt_col - 1;
	row = input->prompt_row - 1;
	len = ft_strlen(input->clipboard) + 1;
	if (input->ls_size - ft_strlen(input->ls) < len)
		double_input_mem(input, term);
	ft_strcat(input->ls, input->clipboard);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
	ft_putrstr_input(input->rrs, input, term);
	col = input->cursor_col - 1;
	row = input->cursor_row - 1;
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
}

void	cut_input_to_clipboard(t_input *input, t_term *term)
{
	int		col;
	int		row;

	col = input->prompt_col - 1;
	row = input->prompt_row - 1;
	copy_input_to_clipboard(input, term);
	input->ls[0] = '\0';
	input->rrs[0] = '\0';
	clear_screen_after_prompt(input, term);
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	get_pos(&input->cursor_row, &input->cursor_col);
}
