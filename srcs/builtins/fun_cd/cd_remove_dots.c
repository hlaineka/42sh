/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_remove_dots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:47:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/26 10:22:06 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_lst_delete(void *data, size_t size)
{
	ft_bzero(data, size);
	free(data);
}

void	cd_remove_dots(t_list *lst)
{
	t_list	*start;
	t_list	*prev;
	t_list	*temp;

	start = lst;
	prev = lst;
	lst = lst->next;
	while (lst)
	{
		if (!ft_strcmp(lst->content, "."))
		{
			prev->next = lst->next;
			ft_lstdelone(&lst, &cd_lst_delete);
			lst = prev->next;
			continue ;
		}
		else if (!ft_strcmp(lst->content, ".."))
		{
			temp = start;
			if (temp == prev)
			{
				prev->next = lst->next;
				ft_lstdelone(&lst, &cd_lst_delete);
				lst = prev->next;
				continue ;
			}
			while (temp->next != prev)
				temp = temp->next;
			temp->next = lst->next;
			ft_lstdelone(&lst, &cd_lst_delete);
			ft_lstdelone(&prev, &cd_lst_delete);
			lst = temp->next;
			prev = temp;
			continue ;
		}
		lst = lst->next;
		prev = prev->next;
	}
}
