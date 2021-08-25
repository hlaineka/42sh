/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 13:16:33 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/25 22:19:01 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

/*
** ${variable}
**    If you write braces around the variable name, then it is completely
**    unambiguous where the variable name ends. You can concatenate additional
**    letters onto the end of the variable value by writing them immediately
**    after the close brace. For example, ‘${foo}s’ expands into ‘tractors’.
**
** You can also use various constructs to modify the value that is substituted,
** or test it in various ways.
**
** ${variable:-default}
**    Substitute the value of variable, but if that is empty or undefined, use
**     default instead.
**
** ${variable:=default}
**    Substitute the value of variable, but if that is empty or undefined, use
**    default instead and set the variable to default.
**
** ${variable:?message}
**    If variable is defined and not empty, substitute its value.
**
** Otherwise, print message as an error message on the standard error
** stream, and consider word expansion a failure.
**
** ${variable:+replacement}
**    Substitute replacement, but only if variable is defined and nonempty.
**    Otherwise, substitute nothing for this construct.
**
** ${#variable}
**    Substitute a numeral which expresses in base ten the number of characters
**    in the value of variable. ‘${#foo}’ stands for ‘7’, because ‘tractor’ is
**    seven characters.
**
** These variants of variable substitution let you remove part of the
** variable’s value before substituting it. The prefix and suffix are not
** mere strings; they are wildcard patterns, just like the patterns that
** you use to match multiple file names. But in this context, they match
** against parts of the variable value rather than against file names.
**
** ${variable%%suffix}
**    Substitute the value of variable, but first discard from that variable
**    any portion at the end that matches the pattern suffix.
**
**    If there is more than one alternative for how to match against suffix,
**    this construct uses the longest possible match.
**
**    Thus, ‘${foo%%r*}’ substitutes ‘t’, because the largest match for ‘r*’ at
**    the end of ‘tractor’ is ‘ractor’.
**
** ${variable%suffix}
**    Substitute the value of variable, but first discard from that variable
**    any portion at the end that matches the pattern suffix.
**
**    If there is more than one alternative for how to match against suffix,
**    this construct uses the shortest possible alternative.
**
**    Thus, ‘${foo%r*}’ substitutes ‘tracto’, because the shortest match for
**    ‘r*’ at the end of ‘tractor’ is just ‘r’.
**
** ${variable##prefix}
**    Substitute the value of variable, but first discard from that variable
**    any portion at the beginning that matches the pattern prefix.
**
**    If there is more than one alternative for how to match against prefix,
**    this construct uses the longest possible match.
**
**    Thus, ‘${foo##*t}’ substitutes ‘or’, because the largest match for ‘*t’
**    at the beginning of ‘tractor’ is ‘tract’.
**
** ${variable#prefix}
**    Substitute the value of variable, but first discard from that variable
**    any portion at the beginning that matches the pattern prefix.
**
**    If there is more than one alternative for how to match against prefix,
**    this construct uses the shortest possible alternative.
**
**    Thus, ‘${foo#*t}’ substitutes ‘ractor’, because the shortest match for
**    ‘*t’ at the beginning of ‘tractor’ is just ‘t’.
*/

char	*get_param_str(char *param, t_term *term)
{
	char	*val;

	if (param[0] == '#')
		return (get_param_length(param + 1, term));
	if (ft_strstr(param, ":-"))
		return (substitute_var_or_default(param, term));
	if (ft_strstr(param, ":="))
		return (substitute_var_or_set_dfl(param, term));
	if (ft_strstr(param, ":+"))
		return (substitute_replacement(param, term));
	if (ft_strstr(param, ":?"))
		return (substitute_var_or_error_msg(param, term));
	if (ft_strstr(param, "##"))
		return (substitute_var_without_prefix(param, term));
	if (ft_strstr(param, "#"))
		return (substitute_var_without_prefix(param, term));
	if (ft_strstr(param, "%"))
		return (substitute_var_without_suffix(param, term));
	val = ft_getenv(param, term->envp);
	if (!val)
		val = ft_getenv(param, term->intern_variables->intern);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}
