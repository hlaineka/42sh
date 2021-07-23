/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_to_hash_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:24:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/23 16:53:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	add_cmd_to_hash_table(char *cmd, char **envp, t_hash *ht, char *fn)
{
	char	*ptr;
	int		i;

	if (is_in_hash_table(cmd, ht))
		return ;
	ptr = find_path_for_cmd(cmd, envp, fn);
	if (!ptr)
		return ;
	i = get_next_hash_table_i(ht);
	if (i < 0 || i > 1024)
		return ;
	ht[i].cmd = ft_strdup(cmd);
	ht[i].path = ptr;
	ht[i].hits = 0;
}
