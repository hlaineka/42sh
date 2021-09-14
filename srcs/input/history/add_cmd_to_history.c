/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_to_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:16:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 15:38:53 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	history[i] = ft_strdup(cmd);
	if (!history[i])
		return (-1);
	ptr = ft_strrchr(history[i], '\n');
	if (ptr)
		*ptr = '\0';
	return (0);
}
