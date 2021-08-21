/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:58:27 by hlaineka          #+#    #+#             */
/*   Updated: 2021/08/20 20:10:57 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** More functions to help with basic tokenization.
*/

/*
** returns 0 when the current tokenstr should be delimited.
*/

int	handle_brackets(char *str, char *source, int *i, int *maintoken)
{
	if (!str[0] && source[*i] == '(')
		*maintoken = tkn_lpar;
	else if (!str[0] && source[*i] == ')')
		*maintoken = tkn_rpar;
	else if (!str[0] && source[*i] == '{')
		*maintoken = tkn_lbrace;
	else if (!str[0] && source[*i] == '}')
		*maintoken = tkn_rbrace;
	else
		return (1);
	str[ft_strlen(str)] = source[*i];
	*i = *i + 1;
	return(0);
}

int	handle_operator_token(char *str, char *source, int *i, int *maintoken)
{
	if (ft_strchr(BRACKETS, source[*i]) && 
		0 == handle_brackets(str, source, i, maintoken))
			return (0);
	else if (ft_strchr(REDIROPS, source[*i]))
	{
		if (*maintoken != tkn_redirop && !ft_is_nbrstr(str))
			return (0);
		else
			*maintoken = tkn_redirop;
	}
	else if ((*maintoken != tkn_operator || *maintoken != tkn_redirop)
		&& str[0])
		return (0);
	else
		*maintoken = tkn_operator;
	str[ft_strlen(str)] = source[*i];
	return (1);
}

int	handle_word_token(char *str, char *source, int *i, int *maintoken)
{
	int	w;

	if (*maintoken != tkn_word)
		return (0);
	w = ft_strlen(str);
	str[w] = source[*i];
	return (1);
}

t_token	*add_subtoken(t_token *current, t_token *sub)
{
	t_token	*returnable;
	t_token	*temp;

	if (!current || !sub)
		return (NULL);
	if (sub->prev)
		sub->prev->next = sub->next;
	if (sub->next)
		sub->next->prev = sub->prev;
	sub->next = NULL;
	returnable = current;
	temp = current->subtokens;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = sub;
		sub->prev = temp;
	}
	else
	{
		returnable->subtokens = sub;
		sub->prev = returnable;
	}
	return (returnable);
}

void	free_tokens_sub(t_token *tokens)
{
	t_token	*temp;
	t_token	*temp_sub;
	t_token	*next_temp;
	t_token	*next_temp_sub;

	temp = tokens;
	while (temp)
	{
		next_temp = temp->next;
		temp_sub = temp->subtokens;
		while (temp_sub)
		{
			next_temp_sub = temp_sub->next;
			free_token(&temp_sub);
			temp_sub = next_temp_sub;
		}
		free_token(&temp);
		temp = next_temp;
	}
}

int	*init_quotearray(t_token *current)
{
	int	*quotearray;

	if (current->quotes)
		ft_memdel((void **)&current->quotes);
	quotearray = malloc(sizeof(int) * ft_strlen(current->value) + 1);
	ft_bzero(quotearray, sizeof(int) * ft_strlen(current->value));
	return (quotearray);
}
