/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lbrace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:46:38 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/21 07:20:13 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_job       *token_lbrace(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	if (!job && current->left->operation == tkn_lbrace)
	{
		//tyhjät sulut
		return NULL;
	}
	else if (current->operation == tkn_lbrace)
	{
		//rekursio on hakenut kaikki ja on nyt oikeassa kaarisulussa, joten
		//palautetaan job. Myös oikea sulku palautuu tähän funktioon ettei tartte kirjoittaa omaa.
		return (job);
	}
	//fork tms tässä kohdassa, kun aletaan hakemaan ja suorittamaan loppuja?
	returnable = tree_traversal(job, current, term);
	//kannattaa varmaan ajaa returnablen jobi tässä kohtaa, ja sitten lopettaa forkki
	return (returnable);
}