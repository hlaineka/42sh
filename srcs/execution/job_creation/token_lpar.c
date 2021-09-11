/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lpar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:33:06 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/11 19:50:03 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//jos on job, siellä on jäljesä oleva operaattori, esim. pipe
//jos current->operation (elikkäs tokeni tai operaattori) on ) haetaan
//tree traversella leftin jutut returnableen (leftissä voi olla joko ( tai
// $( ). Oikea tulee ensin, joten siinä ei tehdä mitään operaatioita, se on
// vähän jämäkomento nyt.
// molemmat operaattorit on asetettu unary-operaattoreiksi, joten niissä voi olla
// lapsia vain vasemmassa haarassa!

#include "execution.h"

t_job       *token_lpar(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	if (!current->left)
		return NULL;
	returnable = NULL;
	if (current->operation == tkn_rpar)
		return (tree_traversal(job, current->left, term));
	if (current->operation == tkn_lpar)
	{
		//asian pihvi, tähän alle se forkki tms ja loppuun sitten forkin
		//odotus ennen kuin poistutaan näistä suluista! jobissa on tosiaan
		// odottamassa se perässä tuleva komento, joten ehkä tässä aloitetaan
		//ns tyhjältä pöydältä eikä sen jobin päälle, joten tree traversal saa
		//nullin ekana parametrina.
		returnable = tree_traversal(NULL, current->left, term);
	}
	return (returnable);
}