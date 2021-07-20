/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:48:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/20 19:24:44 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_21.h"
#include "history.h"
#include "input.h"

int	is_bang_bang(char *str)
{
	if (str[0] == '!' && str[1] == '!' && str[2] == '\0')
		return (1);
	return (0);
}

int	is_bang_number(char *str)
{
	int		i;

	i = 1;
	if (str[0] != '!')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_bang_minus_number(char *str)
{
	int		i;

	i = 2;
	if (str[0] != '!' | str[1] != '-')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** BANG_SELECTOR:
** - takes the whole string "!!/!number/!-number/!word" and returns
**   const char* to history string that should be 
*/

const char	*bang_selector(char *bang_param, t_term *term)
{
	if (!bang_param[0] || !bang_param[1])
		return (NULL);
	if (is_bang_bang(bang_param))
		return (bang_bang_fun(term));
	if (is_bang_number(bang_param))
		return (bang_number_fun(bang_param + 1, term));
	if (is_bang_minus_number(bang_param))
		return (bang_minus_number_fun(bang_param + 2, term));
	return (bang_word_fun(bang_param + 1, term));

}
