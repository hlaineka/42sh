/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:02:38 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/08 11:06:01 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*ptr;
	t_list		*tmp;

	ptr = *alst;
	while (ptr)
	{
		tmp = ptr->next;
		ft_lstdelone(&ptr, del);
		ptr = tmp;
	}
	*alst = NULL;
}
