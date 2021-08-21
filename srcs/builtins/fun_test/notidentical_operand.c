/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notidentical_operand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:50:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 17:44:17 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** s1 != s2
**    True if the strings s1 and s2 are not identical; otherwise, false.
*/

void	notidentical_operand(void *proc)
{
	t_process	*p;

	p = proc;
	p->status = 2;
	if (p->argc > 4)
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	if (p->argc == 3)
		return ((void)err_builtin(E_UNA_OP_EXP, "test", p->argv[1]));
	p->status = 1;
	if (ft_strequ(p->argv[1], p->argv[3]))
		return ;
	p->status = 0;
}
