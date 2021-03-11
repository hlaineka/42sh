/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 19:13:22 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/09 15:17:46 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new_lst)
{
	t_list		*tail;

	if (!(*alst) | !new_lst)
		return ;
	tail = *alst;
	while (tail->next)
		tail = tail->next;
	tail->next = new_lst;
}
