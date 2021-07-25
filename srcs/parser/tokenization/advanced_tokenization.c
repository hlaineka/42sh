/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:01:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/25 12:33:06 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

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
	first = word_assignment_marking(first);
	first = word_expansions(first, term);
	if (remove_quotes)
		first = bang_history(first, term);
	return (first);
}
