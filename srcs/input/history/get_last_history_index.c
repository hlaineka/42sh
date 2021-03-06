/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_history_index.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:20:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/02 17:18:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "history.h"
#include "structs_21.h"

int	get_last_history_index(char **history)
{
	int		i;

	i = 1;
	while (i < HISTORY_SIZE && history[i])
		i++;
	if (i == HISTORY_SIZE)
		return (-1);
	return (i);
}
