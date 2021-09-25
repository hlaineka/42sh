/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_el.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/25 12:05:39 by hhuhtane         ###   ########.fr       */
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
	int			i;
	int			j;
	int			temp_i;

	j = 1;
	if (fc->last == 0)
		fc->last = get_last_history_index(term->history) - 1;
	i = get_fc_el_index(fc->last, fc);
	if (i > fc->last || (options & (1 << R_FLAG)))
	{
		temp_i = fc->last;
		fc->last = i;
		i = temp_i;
	}
	if (i > fc->last)
		j = -1;
	i -= j;
	while (i != fc->last)
	{
		i += j;
		if (options & (1 << N_FLAG))
			ft_printf("\t%s\n", term->history[i]);
		else
			ft_printf("%d\t%s\n", i, term->history[i]);
	}
}
