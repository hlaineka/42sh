/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_null.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:32:13 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 12:01:13 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char	**strarr_add(char **argv, char *command)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	argv[i] = ft_strdup(command);
	return(argv);
}

char	**traverse_nulls(t_node *current, char **argv)
{
	if (!current->left && !current->right)
		return (strarr_add(argv, current->command));
	if (current->left)
		traverse_nulls(current->left, argv);
	if (current->right)
		traverse_nulls(current->right, argv);
	return(argv);
}

t_job	*token_null(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	returnable = NULL;
	if (job && term)
		returnable = job;
	else
		returnable = init_job(term);
	traverse_nulls(current, returnable->first_process->argv);
	returnable->first_process->argc = ft_strarrlen(returnable->first_process->argv);
	return(returnable);
}
