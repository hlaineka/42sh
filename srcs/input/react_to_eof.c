/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react_to_eof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:13:24 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/13 19:37:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	react_to_eof(t_input *input, t_term *term)
{
	if (input->ls[0] || input->rrs[0])
		tputs(term->bl_string, 1, ft_putc);
	else
	{
		if (input->input_mode == HEREDOC_MODE)
		{
			input->ls[0] = 4;
			input->ls[1] = '\0';
		}
		else
			ft_strcpy(input->ls, "exit");
		input->rrs[0] = '\0';
		return (1);
	}
	return (0);
}
