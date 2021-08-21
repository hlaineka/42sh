/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_hash_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:55:33 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/23 16:23:26 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_hash	*find_cmd_hash_table(char *cmd, t_hash *ht)
{
	int		i;

	i = 0;
	while (i < 1024 && ht[i].cmd != NULL)
	{
		if (ft_strequ(ht[i].cmd, cmd))
			return (&ht[i]);
		i++;
	}
	return (NULL);
}

char	*cmd_path_from_hash_table(char *cmd, t_hash *ht)
{
	t_hash	*ht_ptr;

	ht_ptr = find_cmd_hash_table(cmd, ht);
	if (ht_ptr == NULL)
		return (NULL);
	return (ht_ptr[0].path);
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

void	create_full_cmd(char *cmd, t_hash *ht, char *buf)
{
	int		i;

	i = 0;
	while (i < 1024 && ht[i].cmd != NULL)
	{
		if (ft_strequ(ht[i].cmd, cmd))
		{
			ft_strcpy(buf, ht[i].path);
			ft_strcat(buf, "/");
			ft_strcat(buf, cmd);
			return ;
		}
		i++;
	}
}

void	increase_hash_table_hits(char *cmd, t_hash *ht)
{
	t_hash	*ht_ptr;

	ht_ptr = find_cmd_hash_table(cmd, ht);
	if (ht_ptr == NULL)
		return ;
	ht_ptr[0].hits++;
}
