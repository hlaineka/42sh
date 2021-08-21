/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dollarlpar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:48:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/29 20:49:24 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_job       *token_dollarlpar(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	if (!job && current->left->operation == tkn_rpar)
	{
		//tyhjät sulut
		return NULL;
	}
	// tätä ei tarvitse koska token_lpar hanskaa
	//else if (current->operation == tkn_rpar)
	//{
		//rekursio on hakenut kaikki ja on nyt oikeassa sulussa, joten
		//palautetaan job Myös oikea sulku palautuu tähän funktioon ettei tartte kirjoittaa omaa.
		return (job);
	//}
	//fork tms tässä kohdassa, kun aletaan hakemaan ja suorittamaan loppuja?
	returnable = tree_traversal(job, current, term);
	//kannattaa varmaan ajaa returnablen jobi tässä kohtaa, ja sitten lopettaa forkki
	return (returnable);
}