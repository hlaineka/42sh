/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_word_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:02:28 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/12 15:27:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

const char	*bang_word_fun(char *word_str, t_term *term)
{
	int		i;
	int		len;

	len = ft_strlen(word_str);
	i = get_last_history_index(term->history);
	if (i == -1)
		return (NULL);	// todo: error & print no history or something

	while (i > 0)
	{
		i--;
		if (!ft_strncmp(term->history[i], word_str, len))
			return (term->history[i]);
	}
	ft_printf_fd(STDERR_FILENO, "42sh: %s: bad word specifier\n", word_str);
	return (NULL);
}
