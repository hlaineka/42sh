/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_to_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:38:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/23 14:42:29 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	signals_to_default(void)
{
	int		i;

	i  = 1;
	while (i < 32)
	{
		signal(i, SIG_DFL);
		i++;
	}
}
