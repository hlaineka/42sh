/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_to_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:16:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/25 15:16:44 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "input.h"
#include "history.h"
#include "structs_21.h"

int	add_cmd_to_history(char *cmd, char **history)
{
	int		i;
	char	*ptr;

	i = get_last_history_index(history);
	if (i < 0)
		return (-1);
	ptr = ft_strdup(cmd);
	if (!ptr)
		return (-1);
	if (i > HISTORY_SIZE - 2)
		remove_oldest_and_move(g_term, ptr);
	else
		history[i] = ptr;
	ptr = ft_strrchr(ptr, '\n');
	if (ptr)
		*ptr = '\0';
	return (0);
}
