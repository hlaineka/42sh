/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/09/12 10:46:10 by hlaineka         ###   ########.fr       */
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

static void	debug_print_tokens(t_token *tokens, char *function_name)
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

static char	*handle_backslash_remove(char *str, int i)
{
	char	*new;
	int		w;
	int		len;

	len = ft_strlen(str) + 1;
	new = ft_strnew(len + 1);
	w = 0;
	while (w < i)
	{
		new[w] = str[w];
		w++;
	}
	new[w++] = 39;
	i++;
	new[w++] = str[i++];
	new[w++] = 39;
	while (w < len)
		new[w++] = str[i++];
	new[w] = '\0';
	ft_free(str);
	return (new);
}

/*
** ascii 92 == \
*/

char	*remove_backslash(char *str)
{
	int		i;
	bool	single_quoted;
	bool	double_quoted;

	i = 0;
	single_quoted = FALSE;
	double_quoted = FALSE;
	while (str[i])
	{
		if (str[i] == 34)
			double_quoted = !double_quoted;
		if (str[i] == 39)
			single_quoted = !single_quoted;
		if (!single_quoted && !double_quoted && str[i] == 92
			&& str[i + 1] == '\n')
			str = ft_strcut(str, i, i + 2);
		else if (!single_quoted && !double_quoted && str[i] == 92
			&& str[i + 1] != 39)
		{
			str = handle_backslash_remove(str, i);
			i = -1;
		}
		i++;
	}
	return (str);
}

t_token	*check_semicolon(t_token *first, t_term *term)
{
	t_token *temp;
	t_token *returnable;
	t_token *command_first;
	t_node	*root;

	temp = first;
	returnable = first;
	command_first = NULL;
	while (temp)
	{
		if (!command_first)
			command_first = temp;
		if (temp->maintoken == tkn_semi && temp->next)
		{
			returnable = temp->next;
			returnable->prev = NULL;
			temp->next = NULL;
			temp = advanced_tokenization(first, term, 1);
			if (term->intern_variables->flag_debug == 1)
				debug_print_tokens(first, "advanced_tokenization in semicolon");
			root = ast_creator(temp, term);
			execute(root, term);
			command_first = NULL;
			temp = returnable;
		}
		else
			temp = temp->next;
	}
	return(returnable);
}

t_token	*lexer(char *input, t_term *term, int remove_quotes)
{
	t_token	*first;

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
