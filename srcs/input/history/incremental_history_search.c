/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incremental_history_search.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:55:17 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/14 13:47:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

const char	*find_cmd_from_history(char *cmd, char **hist, int len)
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

/*
static int	search_keypress(char *buf, char *hist, t_input *input, t_term *term)
{
	int			len;
	const char	*cmd;

	ret = 0;
	if (is_special_key(buf))
		return (1);
	len = ft_strlen(hist);
	if (len > 1000)
		return (-1);
	hist[len] = buf[0];
	cmd = find_cmd_from_history(hist, term->history, len + 1);
	if (!cmd)
	{
		hist[len] = '\0';
		tputs(term->bl_string, 1, ft_putc);
		return (0);
	}
	return (0);
}
*/


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
	{
		tputs(tgoto(term->cm_string, input->start_col - 1, input->start_row - 1), 1, ft_putc);
		print_prompt(PROMPT_NORMAL);
		get_pos(&input->prompt_row, &input->prompt_col);
		clear_screen_after_prompt(input, term);
		input->input_mode = 0;
		cmd = find_cmd_from_history(input->ls, term->history, len);
		ft_printf("`%s': ", input->ls);
		ft_strcpy(input->ls, cmd);
		ft_strcat(input->ls, "\n");
		return (1);
	}
	input->ls[len] = rc[0];
//	hist[len] = buf[0];
	cmd = find_cmd_from_history(input->ls, term->history, len + 1);
	if (!cmd)
	{
		input->ls[len] = '\0';
		tputs(term->bl_string, 1, ft_putc);
		return (0);
	}
//	ft_strcpy(input->ls, cmd);
	clear_screen_after_prompt(input, term);
	ft_printf("`%s': ", input->ls);
//	tputs(tgoto(term->cm_string, term->prompt_col, term->prompt_row, 1, ft_putc);
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
