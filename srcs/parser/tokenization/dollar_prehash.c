/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_prehash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:12:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/19 20:16:03 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"

char	*get_param_length(char *param, t_term *term)
{
	char	*str;

	str = ft_getenv(param, term->envp);
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	if (!str)
		return (ft_strdup("0"));
	return (ft_itoa(ft_strlen(str)));
}
