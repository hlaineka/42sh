/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdellast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:28:08 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/13 23:38:14 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdellast(t_list **first)
{
	t_list	*last;

	last = *first;
	while (last != NULL && last->next != NULL)
	{
		last = last->next;
	}
}
