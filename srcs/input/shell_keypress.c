/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_keypress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:34:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 14:29:39 by hhuhtane         ###   ########.fr       */
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

static char	*double_allocation(char *str, size_t size)
{
	char	*new;

	new = ft_memalloc(sizeof(char) * size * 2);
	if (!new)
		return (NULL);
	ft_strcat(new, str);
	free(str);
	return (new);
}

static int	double_input_mem(t_input *input, t_term *term)
{
	input->ls = double_allocation(input->ls, input->ls_size); //error check
	input->rrs = double_allocation(input->rrs, input->rrs_size); //error chekc
	input->ls_size *= 2;
	input->rrs_size *= 2;
	return (0);
}

static int	do_special_keys(char *rc, t_input *input, t_term *term)
{
	ft_is_home_key(rc) == TRUE ? home_keypress(input, term) : 0;
	ft_is_end_key(rc) == TRUE ? end_keypress(input, term) : 0;
	ft_is_up_key(rc) == TRUE ? history_up(input, term) : 0;
	ft_is_down_key(rc) == TRUE ? history_down(input, term) : 0;
	ft_is_left_key(rc) == TRUE ? left_keypress(input, term) : 0;
	ft_is_right_key(rc) == TRUE ? right_keypress(input, term) : 0;
	ft_is_delete_key(rc) == TRUE ? delete_keypress(input, term) : 0;
	if (rc[0] == KEY_ESC)
	{
		if (ft_is_right_key(rc + 1))
			move_next_word(input, term);
		else if (ft_is_left_key(rc + 1))
			move_prev_word(input, term);
		else if (ft_is_up_key(rc + 1))
			alt_up_keypress(input, term);
		else if (ft_is_down_key(rc + 1))
			alt_down_keypress(input, term);
	}
	else if (rc[0] == 127)
		backspace_keypress(input, term);
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
