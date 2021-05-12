/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react_to_eof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:13:24 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/07 12:17:05 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	react_to_eof(t_input *input, t_term *term)
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
	return (0);
}
