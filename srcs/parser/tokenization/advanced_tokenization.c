/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:01:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/28 16:07:47 by hlaineka         ###   ########.fr       */
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

t_token	*advanced_tokenization(t_token *first, t_term *term)
{
	first = word_expansions(first, term);
	return (first);
}
