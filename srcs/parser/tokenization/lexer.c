/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/09/28 20:41:50 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "execution.h"

/*
** Lexer is the main function responsible for tokenization. Tokenization is
** divided into three parts, basic tokenization, operator tokenization and
** advanced tokenization. The created tokens are printed, if the shell is
** started in debug mode.
*/

void	debug_print_tokens(t_token *tokens, char *function_name)
{
	t_token	*temp;

	temp = tokens;
	ft_printf_fd(STDOUT_FILENO, "tokens after %s:\n", function_name);
	while (temp)
	{
		ft_printf_fd(STDOUT_FILENO, "%s = %i command: %s, ", temp->value,
			temp->maintoken, temp->full_command);
		temp = temp->next;
	}
	ft_printf_fd(STDOUT_FILENO, "\n");
}

t_token	*lexer(char *input, t_term *term, int remove_quotes)
{
	t_token	*first;

	if (ft_strequ(input, "\n"))
		return (NULL);
	first = NULL;
	input = remove_backslash(input);
	first = define_basic_tokens(input);
	ft_free(input);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tokens(first, "define_basic_tokens");
	first = validate_operator_tokens(first);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tokens(first, "validate_operator_tokens");
	if (remove_quotes)
		first = check_semicolon(first, term);
	first = advanced_tokenization(first, term, remove_quotes);
	if (term->intern_variables->flag_debug == 1)
		debug_print_tokens(first, "advanced_tokenization");
	return (first);
}
