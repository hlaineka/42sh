/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_minus_number_fun.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:28 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/12 14:51:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

const char	*bang_minus_number_fun(char *number_str, t_term *term)
{
	int		n;

	n = ft_atoi(number_str);
	n--;
	if (n < 0)
		return (NULL);	// todo: error & print no history or something
	if (!term->history[n])
		return (NULL);
	return (term->history[n]);
}
