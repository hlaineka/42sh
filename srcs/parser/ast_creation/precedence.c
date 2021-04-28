/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:01:36 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/28 15:52:37 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdbool.h>

/*
** Precedence is the order in which the operations are executed. The shunting
** yard algorithm that changes the token list from infix to postfix notation
** uses precedence to evaluate the order of operators. In token creation,
** the filename of redirection operations is saved in the subtokens, and for
** that reson redirectionoperator are marked as unary operations. pipe |, &&
** and || are also marked as left associative. A null token is added between
** two words, since otherwise the shunting yard algorithm would not work.
*/

int	is_redirectionop(t_token *tkn)
{
	if (tkn && (tkn->maintoken == tkn_io_number || tkn->maintoken == tkn_less
			|| tkn->maintoken == tkn_great || tkn->maintoken == tkn_dless
			|| tkn->maintoken == tkn_dgreat || tkn->maintoken == tkn_lessand
			|| tkn->maintoken == tkn_greatand || tkn->maintoken == tkn_lessgreat
			|| tkn->maintoken == tkn_dlessdash || tkn->maintoken
			== tkn_clobber))
		return (1);
	return (0);
}

/*
** When there are two plain words one after another, a delimiter token needs to
** be added to make sure they bind together in the shunting yard algorithm.
*/

static t_token	*add_delimiter_token(t_token *tkn)
{
	t_token	*new;
	t_token	*temp;

	new = tkn;
	if (tkn->maintoken == tkn_word)
	{
		temp = tkn->prev;
		while (temp && is_redirectionop(temp))
			temp = temp->prev;
		if (temp && (temp->maintoken == tkn_word
				|| temp->maintoken == tkn_lpar))
		{
			new = malloc(sizeof(t_token));
			ft_bzero(new, sizeof(t_token));
			new->value = ft_strdup("(null)");
			new->precedence = 5;
			new->prev = tkn->prev;
			new->next = tkn;
			tkn->prev->next = new;
			tkn->prev = new;
		}
	}
	return (tkn);
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
