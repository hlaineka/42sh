/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_history_index.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:20:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/25 15:14:14 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "history.h"
#include "structs_21.h"

int	get_last_history_index(char **history)
{
	int		i;

	i = 0;
	while (i < HISTORY_SIZE && history[i])
		i++;
	if (i == HISTORY_SIZE)
		return (-1);
	return (i);
}
