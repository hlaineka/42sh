/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/21 10:25:57 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** NOTIONS:
*/

static void	hash_r(t_term *term)
{
	t_hash	*hash_table;
	int		i;

	i = 0;
	hash_table = term->hash_table;
	while (i < 1024 && hash_table[i].cmd != NULL)
	{
		free(hash_table[i].cmd);
		hash_table[i].cmd = NULL;
		free(hash_table[i].path);
		hash_table[i].path = NULL;
		hash_table[i].hits = 0;
		i++;
	}
}

static void	hash_list(t_term *term)
{
	t_hash	*hash_table;
	int		i;

	i = 0;
	hash_table = term->hash_table;
	if (term->hash_table[0].cmd == NULL)
		ft_printf("hash: hash table empty\n");
	else
		ft_printf("hits\tcommand\n");
	while (i < 1024 && hash_table[i].cmd != NULL)
	{
		ft_printf("%4d\t%s/%s\n", hash_table[i].hits,
			hash_table[i].path, hash_table[i].cmd);
		i++;
	}
}

int	get_next_hash_table_i(t_hash *ht)
{
	int		i;

	i = 0;
	while (ht[i].cmd != NULL)
		i++;
	return (i);
}

static void	args_to_hash_table(char **argv, char **envp)
{
	t_term	*term;
	t_hash	*ht;
	int		i;

	i = 1;
	term = g_term;
	ht = term->hash_table;
	while (argv[i])
	{
		add_cmd_to_hash_table(argv[i], envp, ht, "hash");
		i++;
	}
}

void	builtin_hash(void *proc)
{
	int		argc;
	int		options;
	char	**argv;
	char	**envp;

	options = 0;
	argc = ((t_process *)proc)->argc;
	argv = ((t_process *)proc)->argv;
	envp = ((t_process *)proc)->envp;
	if (argc == 1)
		return (hash_list(g_term));
	if (options != 0 && options != (1 << R_FLAG))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "hash", NULL));
	if (options == (1 << R_FLAG))
		return (hash_r(g_term));
	args_to_hash_table(argv, envp);
}
