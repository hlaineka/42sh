/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:44:13 by helvi             #+#    #+#             */
/*   Updated: 2021/05/02 09:19:31 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include "libft.h"

int		ft_lst_length(t_list *first);
void	ft_lst_merge_sort(t_list **first, int (*f)(t_list *elem_a,
				t_list *elem_b));
t_list	*ft_lst_reverse(t_list **first);
t_list	*ft_lst_sorted_merge(t_list *a, t_list *b, int (*f)(t_list *elem_a,
				t_list *elem_b));
void	ft_lst_split(t_list *first, t_list **a, t_list **b);
void	ft_lstaddtoend(const void *content, size_t content_size,
			t_list **beginning);
void	ft_lstdellast(t_list **first);
t_list	*ft_lstend(t_list *beginning);

#endif
