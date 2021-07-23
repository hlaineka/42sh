/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/23 12:42:57 by hhuhtane         ###   ########.fr       */
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

static int	get_next_hash_table_i(t_hash *ht)
{
	int		i;

	i = 0;
	while (ht[i].cmd != NULL)
		i++;
	return (i);
}

static void	args_to_hash_table(char **argv, char **envp, t_process *p)
{
	t_term	*term;
	t_hash	*ht;
	int		i;
	int		j;
	char	*ptr;

	(void)p;
	i = 1;
	term = g_term;
	j = get_next_hash_table_i(term->hash_table);
	ht = term->hash_table;
	while (argv[i])
	{
		ptr = find_path_for_cmd(argv[i], envp, "hash");
		if (ptr)
		{
			ht[j].cmd = ft_strdup(argv[i]); // todo error protection or just leave it?
			ht[j].path = ptr;
			ht[j].hits = 0;
			j++;
		}
		i++;
	}
}

void	builtin_hash(void *proc)
{
	int		i;
	int		argc;
	int		options;
	char	**argv;
	char	**envp;

	i = 0;
	options = 0;
	argc = ((t_process *)proc)->argc;
	argv = ((t_process *)proc)->argv;
	envp = ((t_process *)proc)->envp;
	i = get_argv_options(argv, &options);
	if (argc == 1)
		return (hash_list(g_term));
	if (options != 0 && options != (1 << R_FLAG))
		return ((void)err_builtin(E_ILLEGAL_OPTION, "hash", NULL));
	if (options == (1 << R_FLAG))
		return (hash_r(g_term));
	args_to_hash_table(argv, envp, proc);
}
