/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_hash_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:55:33 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/23 15:01:49 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*cmd_path_from_hash_table(char *cmd, t_hash *ht)
{
	int		i;

	i = 0;
	while (i < 1024 && ht[i].cmd != NULL)
	{
		if (ft_strequ(ht[i].cmd, cmd))
			return (ht[i].path);
		i++;
	}
	return (NULL);

}

int	is_in_hash_table(char *cmd, t_hash *ht)
{
	int		i;

	i = 0;
	while (i < 1024 && ht[i].cmd != NULL)
	{
		if (ft_strequ(ht[i].cmd, cmd))
			return (1);
		i++;
	}
	return (0);
}
