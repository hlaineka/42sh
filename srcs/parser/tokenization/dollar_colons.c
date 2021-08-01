/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_colons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:16:31 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/31 17:07:22 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

static char	*get_colon_minus(char *val, char *word)
{
	if (!val || !val[0])
	{
		if (!word)
			return (ft_strnew(0));
		return (ft_strdup(word));
	}
	return (ft_strdup(val));
}

static char	*get_colon_equal(char *name, char *val, char *word, t_term *term)
{
	if (!val || !val[0])
	{
		if (!word)
			ft_setenv(name, "", 1, term->envp);
		else
			ft_setenv(name, val, 1, term->envp);
	}
	val = ft_getenv(name, term->envp);
	return (ft_strdup(val));
}

static char	*get_colon_question(char *name, char *val, char *word)
{
	if (!val || !val[0])
	{
		if (!word || word[0])
			ft_printf_fd(STDERR_FILENO, "42sh: %s: parameter null or not set\n", name);
		else
			ft_printf_fd(STDERR_FILENO, "42sh: %s: %s\n", name, word);
		return NULL;	//todo this needs to end process and set status 1
	}
	return (ft_strdup(val));
}

static char	*get_colon_plus(char *val, char *word)
{
	if (!val || !val[0])
		return (ft_strnew(0));
	if (!word)
		return (ft_strnew(0));
	return (ft_strdup(word));
}

char	*get_param_colon_word(char *param, char *word, int opt, t_term *term)
{
	char	*str;

	str = ft_getenv(param, term->envp);
//	ft_printf("%s word=%s opt=%d", __FUNCTION__, word, opt);
	if (opt == COLON_MINUS)
		return (get_colon_minus(str, word));
	if (opt == COLON_EQUAL)
		return (get_colon_equal(param, str, word, term));
	if (opt == COLON_QUESTION)
		return (get_colon_question(param, str, word));
	if (opt == COLON_PLUS)
		return (get_colon_plus(str, word));
	return (ft_strnew(0));
}
