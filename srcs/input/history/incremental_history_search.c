/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incremental_history_search.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:55:17 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/20 21:29:39 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

static const char	*cmd_in_history(char *cmd, char **hist, int len)
{
	int		i;

	i = get_last_history_index(hist);
	while (i > 0)
	{
		i--;
		if (!ft_strncmp(cmd, hist[i], len))
			return (hist[i]);
	}
	return (NULL);
}

static int	react_to_enter_history(t_input *input, const char *cmd)
{
	ft_printf("`%s': ", input->ls);
	ft_strcpy(input->ls, cmd);
	ft_strcat(input->ls, "\n");
	return (1);
}

static int	do_special_keys_history(char *rc, t_input *input, t_term *term)
{
	int			ret;
	int			len;
	const char	*cmd;

	ret = 0;
	input->input_mode = 0;
	len = ft_strlen(input->ls);
	if (rc[0] == 3)
	{
		ft_strcpy(input->ls, cmd_in_history(input->ls, term->history, len));
		return (do_ctrl_c_key(input, term));
	}
	clear_screen_after_start(input, term);
	print_prompt(PROMPT_NORMAL);
	get_pos(&input->prompt_row, &input->prompt_col);
	cmd = cmd_in_history(input->ls, term->history, len);
	if (rc[0] == 13)
		return (react_to_enter_history(input, cmd));
	else
	{
		ft_strcpy(input->ls, cmd);
		ft_putstr_input(input->ls, input, term);
		get_pos(&input->cursor_row, &input->cursor_col);
	}
	return (ret);
}

int	incremental_history_search(char *rc, t_input *input, t_term *term)
{
	int			ret;
	int			len;
	const char	*cmd;

	ret = 0;
	len = ft_strlen(input->ls);
	if (len > 1000)
		return (-1);
	if (is_special_key(rc))
		return (do_special_keys_history(rc, input, term));
	input->ls[len] = rc[0];
	cmd = cmd_in_history(input->ls, term->history, len + 1);
	if (!cmd)
	{
		input->ls[len] = '\0';
		tputs(term->bl_string, 1, ft_putc);
		return (0);
	}
	clear_screen_after_prompt(input, term);
	ft_printf("`%s': ", input->ls);
	ft_putstr_input((char *)cmd, input, term);
	return (0);
}

void	history_search_start(t_input *input, t_term *term)
{
	int		row;
	int		col;

	clear_screen_after_prompt(input, term);
	ft_bzero(input->ls, input->ls_size);
	ft_bzero(input->rrs, input->rrs_size);
	input->input_mode = SEARCH_MODE;
	row = input->start_row - 1;
	col = input->start_col - 1;
	tputs(tgoto(term->cm_string, col, row), 1, ft_putc);
	input->prompt_length = print_prompt(PROMPT_SEARCH);
	get_pos(&input->prompt_row, &input->prompt_col);
	input->cursor_row = input->prompt_row;
	input->cursor_col = input->prompt_col;
	input->hist_i = 0;
}
