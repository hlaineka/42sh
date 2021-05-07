/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_keypress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:34:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/07 09:23:08 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

static int	is_special_key(char *rc)
{
	if (rc != 0 && (rc[0] < 32 || rc[0] == 127))
		return (1);
	return (0);
}

static void	do_esc_keys(char *rc, t_input *input, t_term *term)
{
	if (ft_is_home_key(rc))
		home_keypress(input, term);
	else if (ft_is_end_key(rc))
		end_keypress(input, term);
	else if (ft_is_up_key(rc))
		history_up(input, term);
	else if (ft_is_down_key(rc))
		history_down(input, term);
	else if (ft_is_left_key(rc))
		left_keypress(input, term);
	else if (ft_is_right_key(rc))
		right_keypress(input, term);
	else if (ft_is_delete_key(rc))
		delete_keypress(input, term);
	else if (ft_is_right_key(rc + 1))
		move_next_word(input, term);
	else if (ft_is_left_key(rc + 1))
		move_prev_word(input, term);
	else if (ft_is_up_key(rc + 1))
		alt_up_keypress(input, term);
	else if (ft_is_down_key(rc + 1))
		alt_down_keypress(input, term);
}

static int	do_special_keys(char *rc, t_input *input, t_term *term)
{
	if (rc[0] == 25)
		copy_input_to_clipboard(input, term);
	else if (rc[0] == 16)
		paste_clipboard_to_input(input, term);
	else if (rc[0] == 11)
		cut_input_to_clipboard(input, term);
	else if (rc[0] == KEY_ESC)
		do_esc_keys(rc, input, term);
	else if (rc[0] == 127)
		backspace_keypress(input, term);
	if (rc[0] == 4)
	{
		if (input->ls[0] || input->rrs[0])
			tputs(term->bl_string, 1, ft_putc);
		else
		{
			if (input->heredoc)
				ft_strcpy(input->ls, "EOF");
			else
				ft_strcpy(input->ls, "exit");
			input->rrs[0] = '\0';
			return (1);
		}
	}
	if (rc[0] == 13)
		return (1);
	return (0);
}

int	shell_keypress(char *rc, t_input *input, t_term *term)
{
	int		ret;
	int		col;
	int		row;

	ret = 0;
	if (!rc[0])
		return (0);
	if (is_special_key(rc))
		ret = do_special_keys(rc, input, term);
	else
	{
		if (ft_strlen(rc) > (input->ls_size - ft_strlen(input->ls)))
			double_input_mem(input, term);
		ft_strncat(input->ls, rc, 1024);
		ft_putstr_input(rc, input, term);
		get_pos(&input->cursor_row, &input->cursor_col);
		col = input->cursor_col - 1;
		row = input->cursor_row - 1;
		ft_putrstr_input(input->rrs, input, term);
		tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	}
	return (ret);
}
