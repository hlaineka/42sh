/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:59:34 by helvi             #+#    #+#             */
/*   Updated: 2021/10/10 10:11:44 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "includes.h"

/*
** The basic tokenization read the input string and divides it into words,
** operators and redirect operators. It also takes into account quotes and
** backslashes, and creates an array the length of the word in the token
** and marks every index that is quoted to make it easier in the later
** tokenization to single out quoted characters.
*/

static int	find_delimiters(char **source, int *i, char *returnable,
	int *maintoken)
{
	if (ft_strchr(BLANKS, source[0][*i]))
	{
		*i = *i + 1;
		return (0);
	}
	else if (ft_strchr(OPCHARS, source[0][*i]))
	{
		if (0 == handle_operator_token(returnable, *source, i, maintoken))
			return (0);
	}
	else if (0 == handle_word_token(returnable, *source, i, maintoken))
		return (0);
	return (1);
}

static int	get_tokenstr(char **source, int *maintoken, char *returnable)
{
	int		i;

	i = 0;
	while (source[0][i])
	{
		if (-1 == check_quotes(source, &i, returnable, maintoken))
			return (-1);
		if (0 == find_delimiters(source, &i, returnable, maintoken))
			break ;
		i++;
	}
	*source = *source + i;
	if (ft_strlen(returnable) > STR_LENGTH)
	{
		ft_printf_fd(2, "42sh: parsererror: word too long\n");
		return (-1);
	}
	return (0);
}

static int	get_basic_token(char **source, t_token **current)
{
	char	*str;
	int		maintoken;

	maintoken = tkn_word;
	str = NULL;
	while ((!str || !str[0]) && source && *source && source[0][0])
	{
		if (str)
			ft_memdel((void **)(&str));
		str = ft_strnew(ft_strlen(*source));
		if (-1 == get_tokenstr(source, &maintoken, str))
		{
			ft_memdel((void **)(&str));
			return (-1);
		}
	}
	*current = NULL;
	if (str)
	{
		*current = init_token();
		(*current)->value = str;
		(*current)->maintoken = maintoken;
		*current = add_quotearray(*current);
	}
	return (0);
}

static int	get_basic_tokens(char **str_ptr, t_token **returnable)
{
	int		status;
	t_token	*current;
	t_token	*prev;

	current = NULL;
	prev = NULL;
	status = get_basic_token(str_ptr, &current);
	while (status != -1 && current && current->value && current->value[0])
	{
		current->prev = prev;
		if (!prev)
			*returnable = current;
		else
			prev->next = current;
		prev = current;
		status = get_basic_token(str_ptr, &current);
	}
	if (current && status != -1)
		free_token(&current);
	return (status);
}

t_token	*define_basic_tokens(char *input)
{
	t_token	*returnable;
	char	*str_ptr;

	str_ptr = input;
	returnable = NULL;
	if (-1 == get_basic_tokens(&str_ptr, &returnable))
	{
		delete_tokens(returnable);
		returnable = NULL;
	}
	return (returnable);
}
