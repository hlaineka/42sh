/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:57:08 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/18 19:21:23 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

/*
** tkn_operator and tkn_redirop tokens created in the basic tokenization are 
** processed again, and given the actual token is set. In case of redirection
** opertaions, the io_number and/or filename are saved as subtokens.
*/

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
	else if (current->maintoken == tkn_operator || current->maintoken
		== tkn_redirop)
		return (-1);
	return (0);
}

int	handle_and_semi(t_token *first)
{
	t_token	*temp;
	t_token	*temp2;

	temp = first;
	while (temp)
	{
		if (temp->maintoken == tkn_and)
		{
			temp2 = first;
			while (temp2)
			{
				if (temp2->maintoken == tkn_semi)
					return (-1);
				temp2 = temp2->next;
			}
		}
		if (temp->maintoken == tkn_semi)
		{
			temp2 = first;
			while (temp2)
			{
				if (temp2->maintoken == tkn_and)
					return (-1);
				temp2 = temp2->next;
			}
		}
		temp = temp->next;
	}
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
		if (current->maintoken != tkn_word && current->maintoken != tkn_lbrace && current->maintoken != tkn_lpar)
		{	
			if (-1 == handle_basic_optkn(current))
			{
				err_syntax(E_SYNTAX, current->value);
				delete_tokens(first);
				return (NULL);
			}
		}
		current = current->next;
	}
	if (-1 == handle_and_semi(first))
	{
		err_syntax(E_SYNTAX, first->value);
		delete_tokens(first);
		return (NULL);
	}
	return (first);
}
