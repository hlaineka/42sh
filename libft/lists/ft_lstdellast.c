/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdellast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:28:08 by hlaineka          #+#    #+#             */
/*   Updated: 2021/02/25 14:09:48 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/*
** Well this doesn't actually do anything...
*/

void	ft_lstdellast(t_list **first)
{
	t_list	*last;

	last = *first;
	while (last != NULL && last->next != NULL)
	{
		last = last->next;
	}
}
