/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:46:25 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 11:56:19 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	move_nchars_from_s1_to_s2(char *s1, char *s2, int limit, int n)
{
	int		i1;
	int		i2;

	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2);
	if (i1 < 0 || i2 >= limit)
		return ;
	while (n-- > 0)
	{
		s2[i2++] = s1[i1];
		s1[i1--] = '\0';
	}
	s2[i2] = '\0';
}

void	move_char_from_s1_to_s2(char *s1, char *s2, int s2_limit)
{
	int		i1;
	int		i2;

	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2);
	if (i1 < 0 || i2 >= s2_limit)
		return ;
	s2[i2++] = s1[i1];
	s1[i1] = '\0';
	s2[i2] = '\0';
}
