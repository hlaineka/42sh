/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_es.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 07:35:20 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/20 08:50:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "typedefs.h"
#include "execution.h"
#include "job_control.h"
#include "history.h"

int	parse_and_execute(char *cmd, t_term *term)
{
	t_node	*root;

	root = parser(cmd, term);
	execute(root, term);
	return (1);
}

int	fc_es(t_term *term, t_fc *fc, int options)
{
	int		temp_i;
	char	*cmd;

	while (fc->first <= fc->last)
	{
		if (options & (1 << R_FLAG))
			temp_i = fc->last;
		else
			temp_i = fc->first;
		cmd = ft_strdup(term->history[temp_i]);
		parse_and_execute(cmd, term);
		if (options & (1 << R_FLAG))
			fc->last--;
		else
			fc->first++;
		sleep(1);
	}
	return (1);
}
