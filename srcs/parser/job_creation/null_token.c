/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:32:13 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/06 16:58:18 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char	**strarr_add(char **argv, char *command)
{
	char	*temp;
	char	*next;
	int		i;

	next = argv[0];
	argv[0] = ft_strdup(command);
	i = 1;
	while (next)
	{
		temp = argv[i];
		argv[i] = next;
		next = temp;
		i++;
	}
	argv[i] = next;
	return(argv);
}

t_job		*null_token(t_job *job, t_node *current)
{
	if (!current->right || !current->left)
		return (NULL);
	if (current->right->operation == tkn_word)
		strarr_add(job->first_process->argv, current->right->command);
	strarr_add(job->first_process->argv, current->left->command);
	return(job);
}
