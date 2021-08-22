/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp_feat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 16:00:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/22 14:47:47 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"

char	*dollar_split_param(char *param, char *split, int size)
{
	char	*ptr;

	ptr = ft_strstr(param, split);
	ptr[0] = '\0';
	if (size == 2)
		ptr[1] = '\0';
	return (ptr + size);
}

char	*substitute_var_or_default(char *param, t_term *term)
{
	char	*dfl;
	char	*str;

	dfl = dollar_split_param(param, ":-", 2);
	str = ft_getenv(param, term->envp);		//todo which first, intern or envp?
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	param[ft_strlen(param)] = ':';
	param[ft_strlen(param)] = '-';
	if (!str)
	{
		if (!dfl)
			return (NULL);
		str = dfl;
	}
	return (ft_strdup(str));
}

char	*substitute_var_or_set_dfl(char *param, t_term *term)
{
	char	*dfl;
	char	*str;

	dfl = dollar_split_param(param, ":=", 2);
	str = ft_getenv(param, term->envp);		//todo which first, intern or envp?
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	if (!str)
	{
		ft_setenv(param, dfl, 1, term->envp);
		ft_setenv(param, dfl, 1, term->intern_variables->intern);
		str = dfl;
	}
	param[ft_strlen(param)] = ':';
	param[ft_strlen(param)] = '=';
	if (!str)
		return (NULL);
	return (ft_strdup(str));
	
}
