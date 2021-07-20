/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignment_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:44:14 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/20 20:11:44 by hlaineka         ###   ########.fr       */
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
	int		i;
	int		w;
	
	if (current->right)
		return (NULL);
	i = 0;
	while (current->command[i] != '\0' && current->command[i] != '=')
	{
		name[i] = current->command[i];
		i++;
	}
	name[i++] = '\0';
	w = 0;
	while(current->command[i] != '\0')
		value[w++] = current->command[i++];
	value[w] = '\0';
	if (current->left || job)
	{
		if (!job)
		{
			job = init_job(current);
			job->first_process->envp = strarr_copy(term->envp);
		}
		if (ft_getenv(name, term->envp))
			ft_setenv(name, value, 1, term->envp);
		ft_setenv(name, value, 1, job->first_process->envp);
		job = tree_traversal(job, current->left, term);
	}
	else
	{
		job = init_job(current);
		job->first_process->pid = -1; 
		if (ft_getenv(name, term->envp))
			ft_setenv(name, value, 1, term->envp);
		else
			ft_setenv(name, value, 1, term->intern_variables->intern);
	}
	return(job);
}
