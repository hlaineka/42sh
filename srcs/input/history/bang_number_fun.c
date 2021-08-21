/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_number_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:28 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/14 12:47:21 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

/*
void		print_history(t_term *term)
{
	char	**h;
	int		i;

	i = 0;
	h = term->history;
	while (h[i])
	{
		ft_printf("%s[i=%d]: %s\n", __FUNCTION__, i, h[i]);
		i++;
	}
}
*/

const char	*bang_number_fun(char *number_str, t_term *term)
{
	int		n;
	int		i;

//	print_history(term);
	n = ft_atoi(number_str);
	i = get_last_history_index(term->history);
	if (i == -1)
		return (NULL);	// todo: error & print no history or something
	if (n < 0)
		return (NULL);
	if (n >= HISTORY_SIZE || !term->history[n])
		return (NULL);
	return (term->history[n]);
/*
	i = i - n - 1;
	if ((i < 0) || (i > HISTORY_SIZE) || !term->history[i])
		return (NULL);
	return (term->history[i]);
*/
}
