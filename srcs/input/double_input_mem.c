/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_input_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 12:21:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 12:21:29 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char	*double_allocation(char *str, size_t size)
{
	char	*new;

	new = ft_memalloc(sizeof(char) * size * 2);
	if (!new)
		return (NULL);
	ft_strcat(new, str);
	free(str);
	return (new);
}

int	double_input_mem(t_input *input, t_term *term)
{
	input->ls = double_allocation(input->ls, input->ls_size);
	input->rrs = double_allocation(input->rrs, input->rrs_size);
	if (!input->ls || !input->rrs)
		err_fatal(ERR_MALLOC, NULL, term);
	input->ls_size *= 2;
	input->rrs_size *= 2;
	return (0);
}
