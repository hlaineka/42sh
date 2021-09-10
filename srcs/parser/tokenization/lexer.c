/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/09/10 17:05:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** Lexer is the main function responsible for tokenization. Tokenization is
** divided into three parts, basic tokenization, operator tokenization and
** advanced tokenization. The created tokens are printed, if the shell is
** started in debug mode.
*/

static void	debug_print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_printf_fd(STDOUT_FILENO, "tokens after first tokenization:\n");
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

t_token	*lexer(char *input, t_term *term, int remove_quotes)
{
	t_token	*first;

	first = NULL;
	input = remove_backslash(input);
	first = define_basic_tokens(input);
	ft_free(input);
	if (term->intern_variables->flag_debug == 1){
		ft_printf("define_basic_tokens\n");
		debug_print_tokens(first);
	}
	first = validate_operator_tokens(first);
	if (term->intern_variables->flag_debug == 1){
		ft_printf("validate_operator_tokens\n");
		debug_print_tokens(first);
	}
	first = advanced_tokenization(first, term, remove_quotes);
	if (term->intern_variables->flag_debug == 1){
		ft_printf("advanced_tokenization\n");
		debug_print_tokens(first);
	}
	if (!first)
		return (NULL);
	if (remove_quotes)
	{
		add_full_command(first);
		if (term->intern_variables->flag_debug == 1){
			ft_printf("add_full_command\n");
			debug_print_tokens(first);
		}
		quote_removal(first);
	}
	return (first);
}
