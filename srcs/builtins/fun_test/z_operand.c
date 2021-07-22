/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_operand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:50:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 15:56:17 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** -z  pathname
**    True if the length of string string is zero; otherwise, false.
*/

void	z_operand(void *proc)
{
	t_process	*p;

	p = proc;
	p->status = 1;
	if (p->argc > 4)
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	if (p->argc > 3)
		return ((void)err_builtin(E_BIN_OP_EXP, "test", p->argv[3]));
	if (ft_strlen(p->argv[2]))
		return ;
	p->status = 0;	// todo check if this is enough?
}
