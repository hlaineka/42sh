/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:37:51 by helvi             #+#    #+#             */
/*   Updated: 2021/03/13 17:36:18 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "21sh.h"

t_job	*parser(char *input)
{
	t_job *returnable;

	returnable = NULL;
	returnable->command = ft_strdup(input);
	return(returnable);
}