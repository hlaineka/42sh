/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lbrace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:46:38 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 09:15:18 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_job	*token_lbrace(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	if (!job && current->left->operation == tkn_lbrace)
		return (NULL);
	else if (current->operation == tkn_lbrace)
		return (job);
	returnable = tree_traversal(job, current, term);
	return (returnable);
}
