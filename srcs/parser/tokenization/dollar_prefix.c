/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:36:53 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/10 10:36:29 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"

static int	prefix_long(char *var, char *word, char *buf)
{
	if (var == NULL || (*var == '\0' && (word && *word != '\0')))
		return (0);
	if (word == NULL || *word == '\0')
	{
		ft_strcat(buf, var);
		return (1);
	}
	else if (word[0] == '*')
	{
		if (prefix_long(var + 1, word, buf) > 0)
			return (1);
		return (prefix_long(var, word + 1, buf));
	}
	else if (var[0] == word[0])
		return (prefix_long(var + 1, word + 1, buf));
	return (0);
}

char	*remove_longest_prefix(char *var, char *word)
{
	char	buf[2056];

	ft_bzero(buf, 2056);
	if (prefix_long(var, word, buf))
		return (ft_strdup(buf));
	if (var)
		return (ft_strdup(var));
	return (NULL);
}

static int	prefix_shortest(char *var, char *word, char *buf)
{
	if (var == NULL || (*var == '\0' && (word && *word == '\0')))
		return (0);
	if (word == NULL || *word == '\0')
	{
		ft_strcat(buf, var);
		return (1);
	}
	else if (word[0] == '*')
	{
		if (prefix_shortest(var, word + 1, buf) > 0)
			return (1);
		return (prefix_shortest(var + 1, word, buf));
	}
	else if (var[0] == word[0])
		return (prefix_shortest(var + 1, word + 1, buf));
	return (0);
}

char	*remove_shortest_prefix(char *var, char *word)
{
	char	buf[2056];

	ft_bzero(buf, 2056);
	if (prefix_shortest(var, word, buf))
		return (ft_strdup(buf));
	if (var)
		return (ft_strdup(var));
	return (NULL);
}

char	*substitute_var_without_prefix(char *param, t_term *term)
{
	int		opt;
	char	*word;
	char	*str;

	opt = 0;
	if (ft_strstr(param, "##"))
	{
		word = dollar_split_param(param, "##", 2);
		opt = 1;
	}
	else
		word = dollar_split_param(param, "#", 1);
	str = ft_getenv(param, term->envp);
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	if (!str)
		return (NULL);
	param[ft_strlen(param)] = '#';
	if (opt == 0)
		return (remove_shortest_prefix(str, word));
	param[ft_strlen(param)] = '#';
	return (remove_longest_prefix(str, word));
}
