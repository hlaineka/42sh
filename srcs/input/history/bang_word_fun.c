/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_word_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:28 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/12 14:41:45 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

const char	*bang_word_fun(char *word_str, t_term *term)
{
//	int		n;
//	int		i;

	(void)word_str;
	(void)term;
	return ("WORD!");
/*
	n = ft_atoi(number_str);
	i = get_last_history_index(term->history);
	if (i == -1)
		return (NULL);	// todo: error & print no history or something
	i = i - n;
	if (!term->history[i])
		return (NULL);
	return (term->history[i]);
*/
}
