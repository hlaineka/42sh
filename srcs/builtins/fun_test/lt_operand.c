/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lt_operand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:50:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 18:27:19 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** n1 -lt  n2
**    True if the integer n1 is algebraically less than the integer n2;
**    otherwise, false.
*/

void	lt_operand(void *proc)
{
	t_process	*p;

	p = proc;
	p->status = 2;
	if (p->argc > 4)
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	if (p->argc == 3)
		return ((void)err_builtin(E_UNA_OP_EXP, "test", p->argv[1]));
	if (!is_digit_str(p->argv[1]))
		return ((void)err_builtin(E_NOT_INT, "test", p->argv[1]));
	if (!is_digit_str(p->argv[3]))
		return ((void)err_builtin(E_NOT_INT, "test", p->argv[3]));
	p->status = 1;
	if (ft_atoi(p->argv[1]) >= ft_atoi(p->argv[3]))
		return ;
	p->status = 0;
}
