/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_assignment_marking.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:39:32 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 21:26:11 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include "includes.h"

int	check_assignment_word(t_token *tkn)
{
	char	name[STR_LENGTH];
	int		i;
	int		returnable;
	int		i_equal_sign;

	returnable = 1;
	ft_bzero(name, STR_LENGTH);
	i = 0;
	i_equal_sign = ft_str_find_c(tkn->value, '=');
	if (i_equal_sign > 0 && tkn->quotes[i_equal_sign] == 0)
	{
		while (i < i_equal_sign)
		{
			name[i] = tkn->value[i];
			i++;
		}
		name[i] = '\0';
		if (ft_is_name(name))
			tkn->maintoken = tkn_assignment_word;
		else
			returnable = 0;
	}
	else
		returnable = 0;
	return (returnable);
}

int	is_splitting_operator(t_token *tkn)
{
	if (tkn->maintoken == tkn_and || tkn->maintoken == tkn_lpar
		|| tkn->maintoken == tkn_rpar || tkn->maintoken == tkn_semi
		|| tkn->maintoken == tkn_nl || tkn->maintoken == tkn_pipe
		|| tkn->maintoken == tkn_and_if || tkn->maintoken == tkn_or_if
		|| tkn->maintoken == tkn_lbrace || tkn->maintoken == tkn_rbrace
		|| tkn->maintoken == tkn_lesslpar || tkn->maintoken == tkn_greatlpar
		|| tkn->maintoken == tkn_dollarlpar)
		return (1);
	return (0);
}

static void	assign_tkn_assignment(t_token *first)
{
	t_token	*temp;

	temp = first;
	while (temp)
	{
		if (temp->maintoken == tkn_assignment_word)
			temp->maintoken = tkn_assignment;
		temp = temp->next;
	}
}

static void	check_token_assignment(t_token *temp, int *is_first_command_word,
	int *only_assignments)
{
	if (is_splitting_operator(temp))
		*is_first_command_word = 1;
	else if (*is_first_command_word)
	{
		if (check_assignment_word(temp) == 0)
		{
			*only_assignments = 0;
			*is_first_command_word = 0;
		}	
	}
	else
		*only_assignments = 0;
}

t_token	*word_assignment_marking(t_token *first)
{
	t_token	*temp;
	int		is_first_command_word;
	int		only_assignments;

	temp = first;
	only_assignments = 1;
	is_first_command_word = 1;
	while (temp)
	{
		check_token_assignment(temp, &is_first_command_word, &only_assignments);
		temp = temp->next;
	}
	if (!only_assignments)
		assign_tkn_assignment(first);
	return (first);
}
