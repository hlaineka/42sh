/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_direction_keypress.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:35:39 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/15 15:18:49 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	alt_up_keypress(t_input *input, t_term *term)
{
	char	*ls;
	char	*rrs;

	ls = input->ls;
	rrs = input->rrs;
	if (ft_strchr(input->ls, 13) || ft_strchr(input->rrs, 13)
			|| ft_strchr(input->ls, 9) || ft_strchr(input->rrs, 9))
		return ;
	if (ft_strlen(input->ls) > (term->ncolumns - 1))
	{
		move_nchars_from_s1_to_s2(ls, rrs, input->rrs_size, term->ncolumns);
		move_cursor_up(&input->cursor_row, &input->cursor_col, term);
	}
}

void	alt_down_keypress(t_input *input, t_term *term)
{
	char	*ls;
	char	*rrs;

	ls = input->ls;
	rrs = input->rrs;
	if (ft_strchr(input->ls, 13) || ft_strchr(input->rrs, 13)
			|| ft_strchr(input->ls, 9) || ft_strchr(input->rrs, 9))
		return ;
	if (ft_strlen(input->rrs) > (term->ncolumns - 1))
	{
		move_nchars_from_s1_to_s2(rrs, ls, input->ls_size, term->ncolumns);
		move_cursor_down(&input->cursor_row, &input->cursor_col, term);
	}
}
