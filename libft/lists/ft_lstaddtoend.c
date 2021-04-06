/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddtoend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:35:53 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 15:47:07 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/*
** Adds given content to the end of the list.
*/

void	ft_lstaddtoend(const void *content, size_t content_size,
		t_list **beginning)
{
	t_list	*newelem;
	t_list	*temp;

	newelem = malloc(sizeof(t_list));
	newelem->content = (void *)content;
	newelem->content_size = content_size;
	temp = ft_lstend(*beginning);
	if (temp == NULL)
		*beginning = newelem;
	else
		ft_lstaddafter(temp, newelem);
	return ;
}
