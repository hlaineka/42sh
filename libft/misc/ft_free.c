/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:00:59 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/27 17:28:45 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** frees the passed variable, and sets it to NULL
*/

#include "libft.h"

void	ft_free(void *variable)
{
	ft_memdel(&variable);
}
