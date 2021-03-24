/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:33:13 by helvi             #+#    #+#             */
/*   Updated: 2021/03/24 19:45:06 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_node	*init_node()
{
	t_node	*returnable;

	returnable = (t_node*)malloc(sizeof(t_node));
	ft_bzero(returnable, sizeof(t_node));
	return (returnable);
}

