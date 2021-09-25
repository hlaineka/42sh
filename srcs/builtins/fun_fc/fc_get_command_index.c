/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_command_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/25 12:31:32 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "job_control.h"
#include "typedefs.h"
#include "history.h"

static int	cmd_found_in_history(int i, t_fc *fc, t_process *pr, t_term *term)
{
	if (ft_strnstr(term->history[i], pr->argv[fc->i],
			ft_strlen(pr->argv[fc->i])))
	{
		return (i);
	}
	return (0);
}

int	fc_get_command_index(t_fc *fc, t_term *term, t_process *pr)
{
	int			temp;
	int			i;

	if (!pr->argv[fc->i])
		return (0);
	i = get_last_history_index(term->history);
	temp = ft_atoi(pr->argv[fc->i]);
	if (temp >= i)
		return (-1);
	if (temp == 0)
	{
		if (pr->argv[fc->i][0] == '-' && pr->argv[fc->i][1] == '-')
			return (0);
		while (i-- > 0)
		{
			temp = cmd_found_in_history(i, fc, pr, term);
			if (temp == i)
				break ;
		}
	}
	else if (temp < 0)
		temp = get_last_history_index(term->history) + temp - 1;
	fc->i++;
	return (temp);
}
