/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp_feat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 16:00:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/10 10:46:17 by hhuhtane         ###   ########.fr       */
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

char	*substitute_replacement(char *param, t_term *term)
{
	char	*replacement;
	char	*str;

	replacement = dollar_split_param(param, ":+", 2);
	str = ft_getenv(param, term->envp);
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	param[ft_strlen(param)] = ':';
	param[ft_strlen(param)] = '+';
	if (!str || !str[0] || !replacement)
		return (ft_strdup(""));
	return (ft_strdup(replacement));
}

char	*substitute_var_or_default(char *param, t_term *term)
{
	char	*dfl;
	char	*str;

	dfl = dollar_split_param(param, ":-", 2);
	str = ft_getenv(param, term->envp);
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	param[ft_strlen(param)] = ':';
	param[ft_strlen(param)] = '-';
	if (!str)
	{
		if (!dfl)
			return (ft_strdup(""));
		str = dfl;
	}
	return (ft_strdup(str));
}

char	*substitute_var_or_set_dfl(char *param, t_term *term)
{
	char	*dfl;
	char	*str;

	dfl = dollar_split_param(param, ":=", 2);
	str = ft_getenv(param, term->envp);
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
		return (ft_strdup(""));
	return (ft_strdup(str));
}

char	*substitute_var_or_error_msg(char *param, t_term *term)
{
	char	*err_msg;
	char	*str;

	err_msg = dollar_split_param(param, ":?", 2);
	str = ft_getenv(param, term->envp);
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	if (!str)
	{
		ft_printf_fd(STDERR_FILENO, "42sh: %s: %s\n", param, err_msg);
		param[ft_strlen(param)] = ':';
		param[ft_strlen(param)] = '?';
		term->last_return = 1;
		return (NULL);
	}
	param[ft_strlen(param)] = ':';
	param[ft_strlen(param)] = '?';
	return (ft_strdup(str));
}
