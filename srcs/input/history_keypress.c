/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_keypress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:52:51 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 16:15:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "history.h"

void	history_up(t_input *input, t_term *term)
{
	char	*str;
	int		i;

	i = get_last_history_index(term->history);
	if (input->hist_i < HISTORY_SIZE && input->hist_i < i)
		input->hist_i++;
	else
		return ;
	str = term->history[i - input->hist_i];
	if (!str)
		return ;
	clear_screen_after_prompt(input, term);
	ft_bzero(input->ls, input->ls_size);
	ft_bzero(input->rrs, input->rrs_size);
	ft_strcat(input->ls, str);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
}

void	history_down(t_input *input, t_term *term)
{
	char	*str;
	int		i;

	i = get_last_history_index(term->history);
	if (input->hist_i > 0)
		input->hist_i--;
	else
		return ;
	if (input->hist_i == 0)
	{
		ft_bzero(input->ls, input->ls_size);
		ft_bzero(input->rrs, input->rrs_size);
		clear_screen_after_prompt(input, term);
		get_pos(&input->cursor_row, &input->cursor_col);
		return ;
	}
	str = term->history[i - input->hist_i];
	clear_screen_after_prompt(input, term);
	ft_bzero(input->ls, input->ls_size);
	ft_bzero(input->rrs, input->rrs_size);
	ft_strcat(input->ls, str);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
}

int	command_to_history(char *str, t_term *term)
{
	if (add_cmd_to_history(str, term->history))
		return (-1);
	return (0);
}
