/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:46:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/19 15:04:17 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_arg_options(char *arg)
{
	int		options;

	options = 0;
	arg++;
	while (*arg)
	{
		if (!ft_isalpha(*arg))
			return (0);
		options = options | (1 << (*arg - 97));
		arg++;
	}
	return (options);
}

/*
** get_argv_options takes array of arguments and tries to find
**    option flags. the option parameter is set to indicate which flag
**    is on. -a = first bit(1 << 0), -b = second bit (1 << 1), etc.
**    return value is the next index (argv[i]) that is not an option
**    argument.
*/

int	get_argv_options_next(char **argv, int *options)
{
	int		temp;
	int		i;

	i = 0;
	temp = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		temp = get_arg_options(argv[i]);
		if (temp == 0)
			return (i);
		*options = temp | *options;
		i++;
	}
	return (i);
}

int	get_argv_options(char **argv, int *options)
{
	int		temp;
	int		i;

	i = 1;
	temp = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		temp = get_arg_options(argv[i]);
		if (temp == 0)
			return (i);
		*options = temp | *options;
		i++;
	}
	return (i);
}
