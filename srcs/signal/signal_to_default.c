/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_to_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:38:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/27 11:18:23 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	signals_to_default(void)
{
	int		i;

	i = 1;
	while (i < 32)
	{
		signal(i, SIG_DFL);
		i++;
	}
	signal(SIGTSTP, SIG_IGN);
}
