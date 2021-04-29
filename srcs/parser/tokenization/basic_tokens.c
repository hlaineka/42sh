/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:59:34 by helvi             #+#    #+#             */
/*   Updated: 2021/04/28 18:12:53 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** The basic tokenization read the input string and divides it into words,
** operators and redirect operators. It also takes into account quotes and
** backslashes, and creates an array the length of the word in the token
** and marks every index that is quoted to make it easier in the later
** tokenization to single out quoted characters.
*/

char	*get_tokenstr(char **source, int *maintoken)
{
	int		i;
	bool	single_quoted;
	bool	double_quoted;
	bool	backslash;
	char	*returnable;

	i = 0;
	single_quoted = FALSE;
	double_quoted = FALSE;
	backslash = FALSE;
	returnable = ft_strnew(ft_strlen(*source));
	while (source[0][i])
	{
		check_quotes(source[0][i], &single_quoted, &double_quoted);
		check_backslash(returnable, source[0][i], &backslash);
		if (!single_quoted && !double_quoted && !backslash
				&& ft_strchr(BLANKS, source[0][i]))
		{	
			i++;
			break;
		}
		if (!single_quoted && !double_quoted && !backslash && ft_strchr(OPCHARS, source[0][i]))
		{
			if (0 == handle_operator_token(returnable, *source, &i, maintoken))
				break;
		}
		//else if (!single_quoted && !double_quoted && !backslash && ft_strchr(EXPANSIONCHARS, source[0][i]))
		//	check_expansions(returnable, source[0][i]);
		//else if (!single_quoted && !double_quoted && !backslash && source[0][i] == '#')
		//	handle_comment(returnable, *source, &i);
		else if (0 == handle_word_token(returnable, *source, &i, maintoken))
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
	while ((!str || !str[0]) && source && *source && source[0][0])
	{
		if (str)
			ft_free(str);
		str = get_tokenstr(source, &maintoken);
	}
	current = NULL;
	if (str)
	{
		current = init_token();
		current->value = str;
		current->maintoken = maintoken;
		current = add_quotearray(current);
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
	}
	if (current)
		free_token(current);
	return (returnable);
}
