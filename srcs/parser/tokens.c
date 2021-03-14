/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:59:34 by helvi             #+#    #+#             */
/*   Updated: 2021/03/14 12:07:20 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

char		*ft_strtok_r(char *source, char *delimiters, char **current_ptr)
{
	int		i;
	int		w;
	int		start;
	char	*returnable;

	returnable = NULL;
	if (*current_ptr)
		start = ft_strlen(current_ptr);
	else
		start = 0;
	i = 0;
	while (source[i + start])
	{
		w = 0;
		while (delimiters[w])
		{
			if (delimiters[w] == source[i + start])
			{
				returnable = ft_strsub(source, start, i);
				*current_ptr = &source[i + start];
				return (returnable);
			}
			w++;
		}
		i++;
	}
}