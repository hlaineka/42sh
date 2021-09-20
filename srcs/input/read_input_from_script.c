/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_from_script.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:24:30 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 17:19:57 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

static char	*read_line_from_script(int *script_fd, char *str)
{
	char	*tmp;

	if (get_next_line(*script_fd, &str) == 0)
	{
		if (str)
			free(str);
		close(*script_fd);
		*script_fd = -2;
		str = ft_strdup("leaks 42sh");
	}
	ft_asprintf(&tmp, "%s\n", str);
	free(str);
	str = tmp;
	ft_printf("%s\r", str);
	return (str);
}

char	*read_input_from_script(t_term *term)
{
	int		*script_fd;
	char	*str;

	str = NULL;
	script_fd = &term->intern_variables->script_fd;
	if (*script_fd == -1)
	{
		*script_fd = open(term->intern_variables->script_file, O_RDONLY);
		if (*script_fd < 0)
		{
			ft_putendl_fd("Invalid script file", 2);
			exit(1);
		}
	}
	else if (*script_fd == -2)
	{
		str = ft_strdup("exit");
		ft_printf("%s\n\r", str);
		return (str);
	}
	return (read_line_from_script(script_fd, str));
}
