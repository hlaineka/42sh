/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:59:34 by helvi             #+#    #+#             */
/*   Updated: 2021/04/13 12:19:50 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	check_quotes(char c, bool *single_quoted, bool *double_quoted)
{
	if (c == 34)
		*double_quoted = !*double_quoted;
	if (c == 39)
		*single_quoted = !*single_quoted;
}

void	check_backslash(char *str, char c, bool *backslash)
{
	if (c == 92)
		*backslash = TRUE;
	else if (str && str[0] && str[ft_strlen(str) - 1] != 92)
		*backslash = FALSE;
}

bool	ft_is_nbrstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	handle_operator(char *str, char *source, int *i, int *maintoken)
{
	if (ft_strchr(REDIROPS, source[*i]))
	{
		if (*maintoken != tkn_redirop && !ft_is_nbrstr(str))
			return (0);
		else
			*maintoken = tkn_redirop;
	}
	else if ((*maintoken != tkn_operator || *maintoken != tkn_redirop) && str[0])
		return (0);
	else
		*maintoken = tkn_operator;
	str[ft_strlen(str)] = source[*i];
	return (1);
}

static int	handle_word(char *str, char *source, int *i, int *maintoken)
{
	int	w;
	
	if (*maintoken == tkn_operator || *maintoken == tkn_redirop)
		return (0);
	w = ft_strlen(str);
	str[w] = source[*i];
	return (1);
}

char	*get_tokenstr(char **source, int *maintoken)
{
	int		i;
	bool	single_quoted;
	bool	double_quoted;
	bool	backslash;
	char	*returnable;

	if (*source == NULL || source[0][0] == '\0')
		return (NULL);
	i = 0;
	single_quoted = FALSE;
	double_quoted = FALSE;
	backslash = FALSE;
	returnable = ft_strnew(ft_strlen(*source));
	while (source[0][i])
	{
		check_quotes(source[0][i], &single_quoted, &double_quoted);
		check_backslash(returnable, source[0][i], &backslash);
		if (!single_quoted && !double_quoted && !backslash && ft_strchr(BLANKS, source[0][i]))
		{	
			i++;
			break;
		}
		if (!single_quoted && !double_quoted && !backslash && ft_strchr(OPCHARS, source[0][i]))
		{
			if (0 == handle_operator(returnable, *source, &i, maintoken))
				break;
		}
		//else if (!single_quoted && !double_quoted && !backslash && ft_strchr(EXPANSIONCHARS, source[0][i]))
		//	check_expansions(returnable, source[0][i]);
		//else if (!single_quoted && !double_quoted && !backslash && source[0][i] == '#')
		//	handle_comment(returnable, *source, &i);
		else if (0 == handle_word(returnable, *source, &i, maintoken))
			break;
		i++;
	}
	*source = *source + i;
	return (returnable);
}

t_token	*get_basic_token(char **source)
{
	t_token	*current;
	char	*str;
	int		maintoken;

	maintoken = tkn_word;
	str = NULL;
	while (!str && **source)
		str = get_tokenstr(source, &maintoken);
	current = NULL;
	if (str)
	{
		current = init_token();
		current->value = str;
		current->maintoken = maintoken;
	}
	return (current);
}

/*
** The index of every character is marked either by 0, or the ascii
** value of the quoting character that applies. If multiple quotes
** apply at any given point, the sum of those ascii values is in quote_values.
** ascii 35 = " , ascii 39 = ', ascii 92 = \
*/

t_token	*add_quotearray(t_token *current)
{
	int		*quotearray;
	int		i;
	bool	backslash;
	bool	single_quote;
	bool	double_quote;

	if (current)
	{
		quotearray = malloc(sizeof(int) * ft_strlen(current->value));
		ft_bzero(quotearray, sizeof(int) * ft_strlen(current->value));
		double_quote = FALSE;
		single_quote = FALSE;
		backslash = FALSE;
		i = 0;
		while (current->value[i])
		{
			if (current->value[i] == 34)
				double_quote = !double_quote;
			if (current->value[i] == 44)
				single_quote = !single_quote;
			if (current->value[i] == 92)
				backslash = TRUE;
			if (double_quote)
				quotearray[i] = quotearray[i] + 34;
			if (single_quote)
				quotearray[i] = quotearray[i] + 39;
			if (backslash)
				quotearray[i] = quotearray[i] + 92;
			if (current->value[i] != 92 && backslash == TRUE)
				backslash = FALSE;
			i++;
		}
		current->quotes = quotearray;
	}
	return (current);
}

t_token	*define_basic_tokens(char *input)
{
	t_token	*current;
	t_token	*prev;
	t_token	*returnable;
	char	*str_ptr;

	current = NULL;
	prev = NULL;
	str_ptr = input;
	returnable = NULL;
	current = get_basic_token(&str_ptr);
	while (current && current->value && current->value[0])
	{
		current->prev = prev;
		if (!prev)
			returnable = current;
		else
			prev->next = current;
		prev = current;
		current = get_basic_token(&str_ptr);
		current = add_quotearray(current);
	}
	if (current)
		free_token(current);
	return (returnable);
}
