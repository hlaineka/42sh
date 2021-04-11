/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_rows_starting_y.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 11:38:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/11 11:40:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	clear_rows_starting_y(int y, t_term *term)
{
	tputs(tgoto(term->cm_string, 0, y), 1, ft_putc);
	tputs(term->cd_string, 1, ft_putc);
}
