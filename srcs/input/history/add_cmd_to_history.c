/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_to_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:16:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/02 18:22:20 by hhuhtane         ###   ########.fr       */
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

	if (!cmd || (cmd[0] == '\n' && !cmd[1]))
		return (0);
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
