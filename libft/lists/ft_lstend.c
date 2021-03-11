/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:11:01 by hlaineka          #+#    #+#             */
/*   Updated: 2021/02/24 15:55:47 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/*
** Finds the last element of the list.
*/

t_list	*ft_lstend(t_list *beginning)
{
	t_list	*temp;

	temp = beginning;
	while (temp != NULL && temp->next != NULL)
		temp = temp->next;
	return (temp);
}
