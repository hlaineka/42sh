/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_to_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:38:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 12:25:12 by hlaineka         ###   ########.fr       */
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
}
