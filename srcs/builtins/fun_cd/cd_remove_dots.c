/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_remove_dots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:47:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/26 10:46:03 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_lst_delete(void *data, size_t size)
{
	ft_bzero(data, size);
	free(data);
}

static int	cd_remove_dotdot(t_list *start, t_list **prev, t_list **lst)
{
	t_list	*prev_ptr;
	t_list	*lst_ptr;

	prev_ptr = *prev;
	lst_ptr = *lst;
	if (start == prev_ptr)
	{
		prev_ptr->next = lst_ptr->next;
		ft_lstdelone(&lst_ptr, &cd_lst_delete);
		lst_ptr = prev_ptr->next;
		return (1);
	}
	while (start->next != prev_ptr)
		start = start->next;
	start->next = lst_ptr->next;
	ft_lstdelone(&lst_ptr, &cd_lst_delete);
	ft_lstdelone(&prev_ptr, &cd_lst_delete);
	*lst = start->next;
	*prev = start;
	return (0);
}

void	cd_remove_dots(t_list *lst)
{
	t_list	*start;
	t_list	*prev;

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
		}
		else if (!ft_strcmp(lst->content, ".."))
			cd_remove_dotdot(start, &prev, &lst);
		else
		{
			lst = lst->next;
			prev = prev->next;
		}
	}
}
