/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignment_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:44:14 by hlaineka          #+#    #+#             */
/*   Updated: 2021/08/21 10:37:00 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "includes.h"
#include "libft.h"
#include "builtins.h"

static char	**strarr_copy(char **src)
{
	int		i;
	char	**returnable;

	i = 0;
	if (!src)
		return (NULL);
	returnable = malloc(ARGV_SIZE);
	while (src && src[i])
	{
		returnable[i] = ft_strdup(src[i]);
		i++;
	}
	returnable[i] = NULL;
	return (returnable);
}

t_job       *token_assignment_word(t_job *job, t_term *term, t_node *current)
{
	char	name[ARGV_SIZE];
	char	value[ARGV_SIZE];
	
	if (current->right)
		return (NULL);
	get_name_and_value(current->command, value, name);
	if (current->operation == tkn_assignment)
	{
		if (!job)
		{
			job = init_job(current);
			job->first_process->envp = strarr_copy(term->envp);
			job->next = term->jobs->next;
			term->jobs->next = job;
		}
		ft_setenv(name, value, 1, term->envp);
		job = tree_traversal(job, current->left, term);
	}
	else
	{
		if (!job)
		{
			job = init_job(current);
			job->next = term->jobs->next;
			term->jobs->next = job;
		}
		job->first_process->pid = -1; 
		if (ft_getenv(name, term->envp))
			ft_setenv(name, value, 1, term->envp);
		ft_setenv(name, value, 1, term->intern_variables->intern);
		if (current->left)
			job = tree_traversal(job, current->left, term);
	}
	return(job);
}
