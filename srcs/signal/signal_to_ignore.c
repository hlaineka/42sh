/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_to_ignore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:38:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/22 11:37:30 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	signals_to_ignore(void)
{
	int		i;

	i = 1;
	while (i < 32)
	{
		signal(i, SIG_IGN);
		i++;
	}
	signal(SIGTSTP, SIG_IGN);
}
