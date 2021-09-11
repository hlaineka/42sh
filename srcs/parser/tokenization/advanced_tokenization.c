/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:01:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/11 20:27:26 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

t_token *check_paranthesis(t_token *first)
{
	t_token *temp;
	temp = first;
	while(temp)
	{
		if ((temp->maintoken == tkn_lpar || temp->maintoken == tkn_greatlpar
			|| temp->maintoken == tkn_dollarlpar 
			|| temp->maintoken == tkn_lesslpar) && (!temp->next
			|| temp->next->maintoken != tkn_rpar))
		{
			delete_tokens(first);
			ft_printf_fd(2, "wrong amount of paranthesis\n");
			return (NULL);
		}
		else if ((temp->maintoken == tkn_lbrace
			|| temp->maintoken == tkn_dollarlbrace) && (!temp->next
			|| temp->next->maintoken != tkn_rbrace))
		{
			delete_tokens(first);
			ft_printf_fd(2, "wrong amount of braces\n");
			return (NULL);
		}
		temp = temp->next;
	}
	return (first);
}

/*
** Advanced tokenisation checks for these things and marks the with their
** tokens: 
** - assignment_words
** - alias handling, marking and replacement
** - reserved words recognition call
** - positional parameteres check call
** - special parameters and substitution, word expansions, marking and
** replacement
** - field splitting = extra empty character removal that came from expansions
** & aliases
** - pathname extensions
*/

t_token	*advanced_tokenization(t_token *first, t_term *term, int remove_quotes)
{
	first = check_paranthesis(first);
	if (!first)
		return (NULL);
	first = word_assignment_marking(first);
	first = word_expansions(first, term);
	first = alias_handling(first, term, NULL);
	if (remove_quotes)
		first = bang_history(first, term);
	
	return (first);
}
