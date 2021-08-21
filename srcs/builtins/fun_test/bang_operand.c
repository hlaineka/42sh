/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_operand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:50:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 17:33:43 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** !  expression
**    True if expression is false. False if expression is true.
*/

void	bang_operand(void *proc)
{
	t_process	*p;

	p = proc;
	p->status = 1;
	if (p->argc > 4)
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	p->argv++;
	p->argc--;
	builtin_test(p);
	if (p->status == 0)
		p->status = 1;
	else if (p->status == 1)
		p->status = 0;
	p->argv--;
	p->argc++;
}
