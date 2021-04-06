/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:57:08 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 12:50:52 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_token	*combine_optokens(t_token *current, t_token *prev, char *new_value)
{
	ft_free(prev->value);
	prev->value = new_value;
	if (current->next)
		current->next->prev = prev;
	if (prev)
		prev->next = current->next;
	free_token(current);
	return (prev);
}

t_token	*define_doubleop(t_token *current, t_token *prev)
{
	char	*new_value;

	new_value = ft_strjoin(prev->value, current->value);
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
	{
		ft_free(new_value);
		return (current);
	}
	return (combine_optokens(current, prev, new_value));
}

t_token	*define_singleop(t_token *current)
{
	if (ft_strequ(current->value, "|"))
		current->maintoken = tkn_pipe;
	else if (ft_strequ(current->value, "&"))
		current->maintoken = tkn_and;
	else if (ft_strequ(current->value, ";"))
		current->maintoken = tkn_semi;
	else if (ft_strequ(current->value, "("))
		current->maintoken = tkn_lpar;
	else if (ft_strequ(current->value, ")"))
		current->maintoken = tkn_rpar;
	else if (ft_strequ(current->value, "<"))
		current->maintoken = tkn_less;
	else if (ft_strequ(current->value, ">"))
		current->maintoken = tkn_great;
	else
		return (NULL);
	return (current);
}

t_token	*differ_single_and_double_op(t_token *current, t_token *prev)
{
	t_token	*returnable;

	returnable = current;
	if (current && (current->single_quoted || current->double_quoted))
		check_tkn_quotes(current);
	if (!current)
	{
		if (prev && prev->maintoken == tkn_operator)
			returnable = define_singleop(prev);
		else
			returnable = prev;
	}
	else if (ft_strchr(OPCHARS, current->value[0]))
		current->maintoken = tkn_operator;
	else
		current->maintoken = tkn_word;
	if (current && (!prev || prev->maintoken == tkn_word || (prev->maintoken
				!= tkn_operator && current->maintoken == tkn_word)))
		returnable = current;
	else if (current && current->maintoken == tkn_word)
		returnable = define_singleop(prev);
	else if (current)
		returnable = define_doubleop(current, prev);
	return (returnable);
}

t_token	*define_operator_tokens(t_token *first)
{
	t_token	*current;
	t_token	*returnable;
	t_token	*prev;

	current = first;
	prev = NULL;
	while (current)
	{
		current = differ_single_and_double_op(current, prev);
		if (!current)
		{
			ft_printf_fd(2, "operator syntax error\n");
			return (NULL);
		}
		if (!current->prev)
			returnable = current;
		prev = current;
		current = current->next;
	}
	if (!differ_single_and_double_op(current, prev))
	{
		ft_printf_fd(2, "operator syntax error\n");
		return (NULL);
	}
	return (returnable);
}
