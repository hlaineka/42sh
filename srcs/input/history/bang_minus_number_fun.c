/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_minus_number_fun.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:28 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/04 13:07:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

const char	*bang_minus_number_fun(char *number_str, t_term *term)
{
	int		n;
	int		last;

	n = ft_atoi(number_str);
	last = get_last_history_index(term->history);
	if (last == -1)
		return (NULL);
//	n--;
	n = last - n - 1;


	ft_printf("number:%d\n", n);
	if (n < 0 || n >= HISTORY_SIZE)
		return (NULL);	// todo: error & print no history or something
	if (!term->history[n])
		return (NULL);
	return (term->history[n]);
}
