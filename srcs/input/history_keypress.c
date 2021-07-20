/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_keypress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:52:51 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/12 12:36:21 by hhuhtane         ###   ########.fr       */
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

//	if (input->hist_cur->next == NULL)
//		return ;
//	if (!input->hist_cur->next)
//		return ;
//	input->hist_cur = input->hist_cur->next;
//	str = input->hist_cur->content;
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

//	if (input->hist_cur->prev == NULL)
//		return ;
//	input->hist_cur = input->hist_cur->prev;
//	str = input->hist_cur->content;
//	if (!str)
//		return ;
	clear_screen_after_prompt(input, term);
	ft_bzero(input->ls, input->ls_size);
	ft_bzero(input->rrs, input->rrs_size);
	ft_strcat(input->ls, str);
	ft_putstr_input(input->ls, input, term);
	get_pos(&input->cursor_row, &input->cursor_col);
}

int	command_to_history(char *str, t_term *term)
{
//	t_clist	*new;

	if (add_cmd_to_history(str, term->history))
		return (-1);
/*
	new = ft_clstnew(str, ft_strlen(str) + 1);
	if (!new)
		return (NULL);
*/
//	ptr = ft_strrchr(new->content, '\n');
//	*ptr = '\0';
/*
	new->prev = input->last_comm;
	new->next = input->history;
	input->history->prev = new;
	input->last_comm->next = new;
	return (new);
*/
	return (0);
}
