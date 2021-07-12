/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_bang_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:28 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/12 14:30:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

const char	*bang_bang_fun(t_term *term)
{
	int		i;

	i = get_last_history_index(term->history);
	if (i == -1)
		return (NULL);	// todo: error & print no history or something
//	cmd = ft_strdup(term->history[i]);
	return (term->history[i]);
}
