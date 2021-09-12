/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:01:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/12 14:47:02 by hlaineka         ###   ########.fr       */
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

static void	debug_print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_printf_fd(STDOUT_FILENO, "tokens after advanced tokenization:\n");
	while (temp)
	{
		ft_printf_fd(STDOUT_FILENO, "%s = %i command: %s, ", temp->value,
			temp->maintoken, temp->full_command);
		temp = temp->next;
	}
	ft_printf_fd(STDOUT_FILENO, "\n");
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
	if (remove_quotes)
		add_full_command(first);
	if (!first)
		return (NULL);
	first = word_assignment_marking(first);
	first = word_expansions(first, term);
	if (remove_quotes)
	{
		first = alias_handling(first, term, NULL);
		first = bang_history(first, term);
	}
	if (term->intern_variables->flag_debug == 1){
		ft_printf_fd(STDOUT_FILENO,"advanced_tokenization\n");
		debug_print_tokens(first);
	}
	if (!first)
		return (NULL);
	if (remove_quotes)
	{
		if (term->intern_variables->flag_debug == 1){
			ft_printf_fd(STDOUT_FILENO,"add_full_command\n");
			debug_print_tokens(first);
		}
		quote_removal(first);
	}
	return (first);
}
