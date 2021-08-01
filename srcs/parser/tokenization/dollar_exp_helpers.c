/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 13:16:33 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/01 13:19:47 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

/*
** ${#parameter}
**   String Length. The length in characters of the value of parameter shall
**   be substituted. If parameter is '*' or '@', the result of the expansion
**   is unspecified. If parameter is unset and set -u is in effect, the
**   expansion shall fail.
**
** The following four varieties of parameter expansion provide for substring
** processing. In each case, pattern matching notation (see Pattern Matching
** Notation), rather than regular expression notation, shall be used to
** evaluate the patterns. If parameter is '#', '*', or '@', the result of the
** expansion is unspecified. If parameter is unset and set -u is in effect,
** the expansion shall fail. Enclosing the full parameter expansion string in
** double-quotes shall not cause the following four varieties of pattern
** characters to be quoted, whereas quoting characters within the braces
** shall have this effect. In each variety, if word is omitted, the empty
** pattern shall be used.
**
** ${parameter%[word]}
Remove Smallest Suffix Pattern. The word shall be expanded to produce a pattern. The parameter expansion shall then result in parameter, with the smallest portion of the suffix matched by the pattern deleted. If present, word shall not begin with an unquoted '%'.
${parameter%%[word]}
Remove Largest Suffix Pattern. The word shall be expanded to produce a pattern. The parameter expansion shall then result in parameter, with the largest portion of the suffix matched by the pattern deleted.
${parameter#[word]}
Remove Smallest Prefix Pattern. The word shall be expanded to produce a pattern. The parameter expansion shall then result in parameter, with the smallest portion of the prefix matched by the pattern deleted. If present, word shall not begin with an unquoted '#'.
${parameter##[word]}
Remove Largest Prefix Pattern. The word shall be expanded to produce a pattern. The parameter expansion shall then result in parameter, with the largest portion of the prefix matched by the pattern deleted.
*/

int	get_subst_option(char *param, char **colon)
{
	int		options;
	int		len;

	options = 0;
	len = ft_strlen(param);
	*colon = ft_strchr(param, ':');
	if (param[0] == '#')
		options = PRE_HASH;
	else if (param[len - 1] == '%')
	{
		if (param[len - 2] == '%')
		{
			options = DPROCENT;
		}
		else
			options = PROCENT;
	}
	else if (*colon)
	{
		if (colon[0][1] == '-')
		{
			options = COLON_MINUS;
			return (COLON_MINUS);
		}
		else if (colon[0][1] == '=')
			options = COLON_EQUAL;
		else if (colon[0][1] == '?')
			options = COLON_QUESTION;
		else if (colon[0][1] == '+')
			options = COLON_PLUS;
	}
	else if (param[len - 1] == '#')
	{
		if (param[len - 2] == '#')
			options = POST_HASH;
		else
			options = POST_DHASH;
	}
	else
		options = 0;
	return (options);
}

char	*get_param_str(char *param, t_term *term)
{
//	char	*word;
	char	*whitespace;
	int		option;

	if (param[0] == '#')
		return (get_param_length(param + 1, term));
	option = get_subst_option(param, &whitespace);
	if (whitespace && whitespace[0])
	{
		whitespace[0] = '\0';
		whitespace[1] = '\0';
		return (get_param_colon_word(param, whitespace + 2, option, term));
	}
	return (ft_strdup("VAKIO TESTI MUU"));
}
