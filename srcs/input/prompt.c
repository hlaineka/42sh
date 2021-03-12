/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:10:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/12 16:13:28 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	print_prompt(int mode)
{
	if (mode) // change 1 to QUOTED or something like that
		ft_printf("$> ");
	else
		ft_printf("> "); // quote
}
