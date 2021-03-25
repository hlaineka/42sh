/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:08:31 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/24 17:01:39 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*returnable;
	t_list	*returnable_temp;
	t_list	*returnable_previous;

	returnable = (t_list *)malloc(sizeof(t_list));
	if (!returnable)
		return (NULL);
	returnable = f(lst);
	returnable->next = NULL;
	temp = lst->next;
	returnable_previous = returnable;
	while (temp)
	{
		returnable_temp = (t_list *)malloc(sizeof(t_list));
		if (!returnable_temp)
			return (NULL);
		returnable_temp = f(temp);
		returnable_temp->next = NULL;
		returnable_previous->next = returnable_temp;
		returnable_previous = returnable_temp;
		temp = temp->next;
	}
	return (returnable);
}
