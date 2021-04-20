/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:57:08 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/20 11:58:47 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

int	handle_tkn_io_number(t_token *current)
{
	int		i;
	t_token	*new_subtoken;

	i = 0;
	new_subtoken = NULL;
	while (current->value[i] && ft_isdigit(current->value[i]))
		i++;
	if (!ft_strchr(OPCHARS, current->value[i]))
		return (-1);
	if (i > 0)
	{
		new_subtoken = init_token();
		new_subtoken->maintoken = tkn_io_number;
		new_subtoken->value = ft_strcut(current->value, 0, i);
		add_subtoken(current, new_subtoken);
	}
	return (0);
}

int	add_filename_tkn(t_token *current)
{
	if (!current->next || current->next->maintoken != tkn_word)
		return (-1);
	add_subtoken(current, current->next);
	return (0);
}

int	handle_redirection_op(t_token *current)
{
	if (ft_strlen(current->value) > 2)
		return (-1);
	else if (ft_strequ(current->value, "<"))
		current->maintoken = tkn_less;
	else if (ft_strequ(current->value, ">"))
		current->maintoken = tkn_great;
	else if (ft_strequ(current->value, "<<"))
		current->maintoken = tkn_dless;
	else if (ft_strequ(current->value, ">>"))
		current->maintoken = tkn_dgreat;
	else if (ft_strequ(current->value, "<&"))
		current->maintoken = tkn_lessand;
	else if (ft_strequ(current->value, ">&"))
		current->maintoken = tkn_greatand;
	else if (ft_strequ(current->value, "<>"))
		current->maintoken = tkn_lessgreat;
	else if (ft_strequ(current->value, ">|"))
		current->maintoken = tkn_clobber;
	else
		return (0);
	return (add_filename_tkn(current));
}

int	handle_operation(t_token *current)
{
	if (ft_strequ(current->value, "|"))
		current->maintoken = tkn_pipe;
	else if (ft_strequ(current->value, "&"))
		current->maintoken = tkn_and;
	else if (ft_strequ(current->value, ";"))
		current->maintoken = tkn_semi;
	else if (ft_strequ(current->value, "&&"))
		current->maintoken = tkn_and_if;
	else if (ft_strequ(current->value, "||"))
		current->maintoken = tkn_or_if;
	else if (ft_strequ(current->value, "!"))
		current->maintoken = tkn_bang;
	else if (ft_strequ(current->value, ";;"))
		current->maintoken = tkn_dsemi;
	else if (current->maintoken == tkn_operator || current->maintoken == tkn_redirop)
		return (-1);
	return (0);
}

int	handle_basic_optkn(t_token *current)
{
	int	returnable;

	returnable = 0;
	returnable = handle_tkn_io_number(current);
	if (returnable != -1)
		returnable = handle_redirection_op(current);
	if (returnable != -1)
		returnable = handle_operation(current);
	return (returnable);
}

t_token	*validate_operator_tokens(t_token *first)
{
	t_token	*current;

	if (!first)
		return (NULL);
	current = first;
	while (current)
	{
		if (current->maintoken != tkn_word)
		{	
			if (-1 == handle_basic_optkn(current))
			{
				ft_printf_fd(2, "syntax error near token %s\n", current->value);
				free_tokens(first);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (first);
}
