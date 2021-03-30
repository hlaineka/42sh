/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:32:13 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/28 11:33:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "includes.h"
#include "libft.h"

int		null_token(t_token **stack, t_job *executable)
{
	int		returnable;
	int		i;
	
	returnable = 0;
	i = 0;
	if (!*stack)
	{
		ft_printf_fd(2, "syntax error");
		returnable = -1;
	}
	else
	{
		while (executable->first_process->argv[i])
			i++;
		executable->first_process->argv[i++] = (*stack)->value;
		*stack = delete_token(*stack);
		executable->first_process->argv[i++] = (*stack)->value;
		*stack = delete_token(*stack);
	}

}