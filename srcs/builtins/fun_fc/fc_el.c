/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_el.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/22 22:35:03 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"
#include "history.h"

static int	get_fc_el_index(int last, t_fc *fc)
{
	if (fc->first)
		return (fc->first);
	else if (last > 15)
		return (last - 15);
	return (1);
}

void	fc_el(t_term *term, t_fc *fc, int options)
{
	int			last;
	int			i;
	int			temp_i;

	if (fc->last)
		last = fc->last;
	else
		last = get_last_history_index(term->history) - 1;
	i = get_fc_el_index(last, fc);
	while (i <= last)
	{
		if (options & (1 << R_FLAG))
			temp_i = last;
		else
			temp_i = i;
		if (options & (1 << N_FLAG))
			ft_printf("\t%s\n", term->history[temp_i]);
		else
			ft_printf("%d\t%s\n", temp_i, term->history[temp_i]);
		if (options & (1 << R_FLAG))
			last--;
		else
			i++;
	}
}
