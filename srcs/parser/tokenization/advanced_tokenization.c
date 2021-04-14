/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:01:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/13 12:15:44 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*path_extensions(t_token *first)
{
	return (first);
}

void	tilde_expansion(char *str)
{
	
}

t_token *word_expansions(t_token *first)
{
	t_token *temp;

	temp = first;
	while (temp)
	{
		if (ft_strchr(temp->value, '~'))
			tilde_expansion(temp->value);
	}
}

t_token	*advanced_tokenization(t_token *first)
{
	//assignment_words
	//alias handling call
	//reserved words recognition call
	//positional parameteres check call
	//special parameters and substitution, word expansions
	//field splitting = extra empty character removal that came from expansions & aliases
	//pathname extensions
}