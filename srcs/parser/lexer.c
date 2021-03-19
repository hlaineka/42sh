/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:32:48 by helvi             #+#    #+#             */
/*   Updated: 2021/03/18 16:31:11 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
# include "libft.h"

/*
** The index of every character is marked either by 0, or the ascii
** value of the quoting character that applies. If multiple quotes
** apply at any given point, the sum of those ascii values is in quote_values.
*/

void	check_tkn_quotes(t_token *current)
{
	int		*quote_values;
	bool	single_quote;
	bool	double_quote;
	int		i;

	quote_values = (int*)malloc(sizeof(int) * ft_strlen(current->value));
	ft_bzero(quote_values, ft_strlen(current->value));
	double_quote = FALSE;
	single_quote = FALSE;
	i = 0;
	while (current->value[i])
	{
		if (current->value[i] == 34)
			double_quote = !double_quote;
		if (current->value[i] == 44)
			single_quote = !single_quote;
		if (double_quote)
			quote_values[i] = quote_values[i] + 34;
		if (single_quote)
			quote_values[i] = quote_values[i] + 39;
		//add backslash handling here.
		i++;			
	}
	current->tokens = quote_values;
}

void	free_token(t_token **to_free)
{
	if ((*to_free)->tokens)
		ft_free((*to_free)->tokens);
	if ((*to_free)->value)
		ft_free((*to_free)->value);
	ft_free(*to_free);
	*to_free = NULL;
}

bool	combine_optokens(t_token **current, t_token *prev)
{
	char	*new_value;

	new_value = ft_strjoin(prev->value, (*current)->value);
	if (ft_strequ(new_value, "&&"))
		prev->maintoken = tkn_and_if;
	else if (ft_strequ(new_value, "||"))
		prev->maintoken = tkn_or_if;
	else if (ft_strequ(new_value, ";;"))
		prev->maintoken = tkn_dsemi;
	else if (ft_strequ(new_value, "<<"))
		prev->maintoken = tkn_dless;
	else if (ft_strequ(new_value, ">>"))
		prev->maintoken = tkn_dgreat;
	else if (ft_strequ(new_value, "<&"))
		prev->maintoken = tkn_lessand;
	else if (ft_strequ(new_value, ">&"))
		prev->maintoken = tkn_greatand;
	else if (ft_strequ(new_value, "<>"))
		prev->maintoken = tkn_lessgreat;
	else if (ft_strequ(new_value, ">|"))
		prev->maintoken = tkn_clobber;
	else
		return (TRUE);
	ft_free(prev->value);
	prev->value = new_value;
	prev->next = (*current)->next;
	if (prev->next)
		prev->next->prev = prev;
	free_token(current);
	return (TRUE);
}

bool	check_singleop(t_token **current)
{
	if (ft_strequ((*current)->value, "|"))
		(*current)->maintoken = tkn_pipe;
	else if (ft_strequ((*current)->value, "&"))
		(*current)->maintoken = tkn_and;
	else if (ft_strequ((*current)->value, ";"))
		(*current)->maintoken = tkn_semi;
	else if (ft_strequ((*current)->value, "("))
		(*current)->maintoken = tkn_lpar;
	else if (ft_strequ((*current)->value,")"))
		(*current)->maintoken = tkn_rpar;
	else if (ft_strequ((*current)->value, "<"))
		(*current)->maintoken = tkn_less;
	else if (ft_strequ((*current)->value, ">"))
		(*current)->maintoken = tkn_great;
	else
		return (FALSE);
	return(TRUE);		
}

bool	check_tkn_ops(t_token **current, t_token *prev)
{
	if (!current || !*current)
	{
		if (prev && prev->maintoken == tkn_operator)
			if (!(check_singleop(&prev)))
				return (FALSE);
		return (TRUE);
	}
	if (ft_strchr(OPCHARS, (*current)->value[0]))
		(*current)->maintoken = tkn_operator;
	else
		(*current)->maintoken = tkn_word;
	if (!prev || prev->maintoken == tkn_word ||
		(prev->maintoken != tkn_operator && (*current)->maintoken == tkn_word))
		return (TRUE);
	if ((*current)->maintoken == tkn_word)
	{
		if (!(check_singleop(&prev)))
			return (FALSE);
	}
	else
		combine_optokens(current, prev);
	return (TRUE);
}

bool	check_token(t_token **current, t_token *prev)
{
	if (current && *current && ((*current)->single_quoted || (*current)->double_quoted))
		check_tkn_quotes(*current);
	if (!check_tkn_ops(current, prev))
	{
		ft_printf_fd(2, "operator syntax error");
		return (FALSE);
	}
	return (TRUE);
}

bool	check_tokens(t_token **first)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;
	
	current = *first;
	prev = NULL;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (!check_token(&current, prev))
			return(FALSE);
		if (current && !current->prev)
			*first = current;
		prev = current;
		current = next;
	}
	
	check_token(NULL, prev);
	return (TRUE);
}


t_token	*lexer(char *input)
{
	t_token	*first;
	t_token	*current;
	t_token	*prev;
	char	*str_ptr;
	
	first = NULL;
	prev = NULL;
	current = NULL;
	str_ptr = input;
	current = get_token(METACHARS, &str_ptr);
	while (current && current->value && current->value[0])
	{
		current->prev = prev;
		if (!prev)
		{
			first = current;
			//assignment_word check
		}
		else
			prev->next = current;
		prev = current;
		current = get_token(METACHARS, &str_ptr);
	}
	if (!check_tokens(&first))
		return (NULL);
	//comment handling here.
	//IO_NUMBER handling
	return (first);
}
