/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 19:13:22 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/07/27 20:06:46 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list		*tail;

	if (!(*alst) | !new)
		return ;
	tail = *alst;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
}
