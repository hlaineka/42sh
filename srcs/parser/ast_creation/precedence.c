/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:01:36 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/11 12:01:36 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdbool.h>

/*
** When there are two plain words one after another, a delimiter token needs to
** be added to make sure they bind together in the shunting yard algorithm.
*/
//do we need one with rpar?
static t_token	*add_delimiter_token(t_token *tkn)
{
	t_token	*new;

	new = tkn;
	if (tkn->maintoken == tkn_word && tkn->next && (tkn->next->maintoken
			== tkn_word || tkn->next->maintoken == tkn_lpar))
	{
		new = malloc(sizeof(t_token));
		ft_bzero(new, sizeof(t_token));
		new->value = ft_strdup("(null)");
		new->precedence = 5;
		tkn->next->prev = new;
		new->next = tkn->next;
		tkn->next = new;
		new->prev = tkn;
	}
	return (new);
}

/*
** The precedence value determines the order the operator are added after
** words in the shunting yard algorithm. The order of precedence is:
** null-token (binding to words together) == 5
** all redirection operations == 4
** pipe | == 3
** && and || == 2
** ; and & == 1
** tkn_word == 0
** pipe |, && and || are also marked as left associative.
*/

t_token	*add_precedence(t_token *first)
{
	t_token	*temp;

	temp = first;
	while (temp)
	{
		temp->left_associative = FALSE;
		temp = add_delimiter_token(temp);
		if (temp->maintoken == tkn_less || temp->maintoken == tkn_great
			|| temp->maintoken == tkn_dless || temp->maintoken == tkn_dgreat
			|| temp->maintoken == tkn_lessand || temp->maintoken == tkn_greatand
			|| temp->maintoken == tkn_lessgreat || temp->maintoken
			== tkn_dlessdash || temp->maintoken == tkn_clobber)
			temp->precedence = 4;
		else if (temp->maintoken == tkn_pipe)
			temp->precedence = 3;
		else if (temp->maintoken == tkn_and_if || temp->maintoken == tkn_or_if)
			temp->precedence = 2;
		else if (temp->maintoken == tkn_semi || temp->maintoken == tkn_and)
			temp->precedence = 1;
		if (temp->maintoken == tkn_pipe || temp->maintoken == tkn_and_if
			|| temp->maintoken == tkn_or_if)
			temp->left_associative = TRUE;
		temp = temp->next;
	}
	return (first);
}
