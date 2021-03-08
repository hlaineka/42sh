/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:46:29 by hlaineka          #+#    #+#             */
/*   Updated: 2021/02/24 15:32:52 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts how many strings there is in a NULL terminated string array.
*/

int	ft_array_length(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}
