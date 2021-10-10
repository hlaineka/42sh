/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:36:53 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/10 10:36:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parser.h"

static int	suffix_long(char *var, char *word, char *buf, int i)
{
	char	temp;

	if (var == NULL || (i < 0 && (word != NULL && *word != '\0')))
		return (0);
	if (word == NULL || *word == '\0')
	{
		temp = var[i + 1];
		var[i + 1] = '\0';
		ft_strcat(buf, var);
		var[i + 1] = temp;
		return (1);
	}
	else if (word[0] == '*')
	{
		if (suffix_long(var, word, buf, i - 1) > 0)
			return (1);
		return (suffix_long(var, word + 1, buf, i));
	}
	else if (var[i] == word[0])
		return (suffix_long(var, word + 1, buf, i - 1));
	return (0);
}

char	*remove_longest_suffix(char *var, char *word)
{
	char	buf[2056];
	int		i;

	i = ft_strlen(var) - 1;
	ft_bzero(buf, 2056);
	if (suffix_long(var, word, buf, i))
		return (ft_strdup(buf));
	if (var)
		return (ft_strdup(var));
	return (NULL);
}

static int	suffix_shortest(char *var, char *word, char *buf, int i)
{
	char	temp;

	if (var == NULL || (i < 0 && (word != NULL && *word != '\0')))
		return (0);
	if (word == NULL || *word == '\0')
	{
		temp = var[i + 1];
		var[i + 1] = '\0';
		ft_strcat(buf, var);
		var[i + 1] = temp;
		return (1);
	}
	else if (word[0] == '*')
	{
		if (suffix_shortest(var, word + 1, buf, i) > 0)
			return (1);
		return (suffix_shortest(var, word, buf, i - 1));
	}
	else if (var[i] == word[0])
		return (suffix_shortest(var, word + 1, buf, i - 1));
	return (0);
}

static char	*remove_shortest_suffix(char *var, char *word)
{
	char	buf[2056];
	int		i;

	i = ft_strlen(var) - 1;
	ft_bzero(buf, 2056);
	if (suffix_shortest(var, word, buf, i))
		return (ft_strdup(buf));
	if (var)
		return (ft_strdup(var));
	return (NULL);
}

char	*substitute_var_without_suffix(char *param, t_term *term)
{
	int		opt;
	char	*word;
	char	*str;
	char	rev_suffix[2056];

	opt = 0;
	ft_bzero(rev_suffix, 2056);
	if (ft_strstr(param, "%%"))
	{
		word = dollar_split_param(param, "%%", 2);
		opt = 1;
	}
	else
		word = dollar_split_param(param, "%", 1);
	str = ft_getenv(param, term->envp);
	if (!str)
		str = ft_getenv(param, term->intern_variables->intern);
	if (!str)
		return (NULL);
	ft_strrcat(rev_suffix, word);
	param[ft_strlen(param)] = '%';
	if (opt == 0)
		return (remove_shortest_suffix(str, rev_suffix));
	param[ft_strlen(param)] = '%';
	return (remove_longest_suffix(str, rev_suffix));
}
