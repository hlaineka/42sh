/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 10:54:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/28 11:39:16 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **alst)
{
	t_list		*prev_l;
	t_list		*curr_l;
	t_list		*next_l;

	curr_l = *alst;
	prev_l = NULL;
	next_l = NULL;
	while (curr_l)
	{
		next_l = curr_l->next;
		curr_l->next = prev_l;
		prev_l = curr_l;
		curr_l = next_l;
	}
	*alst = prev_l;
}
