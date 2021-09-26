/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dollarlpar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:48:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 09:18:06 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_job	*token_dollarlpar(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	if (!job && current->left->operation == tkn_rpar)
		return (NULL);
	return (job);
	returnable = tree_traversal(job, current, term);
	return (returnable);
}
