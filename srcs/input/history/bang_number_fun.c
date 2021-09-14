/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_number_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:28 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 15:40:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

const char	*bang_number_fun(char *number_str, t_term *term)
{
	int		n;
	int		i;

	n = ft_atoi(number_str);
	i = get_last_history_index(term->history);
	if (i == -1)
		return (NULL);
	if (n <= 0)
		return (NULL);
	if (n >= HISTORY_SIZE || !term->history[n])
		return (NULL);
	return (term->history[n]);
}
