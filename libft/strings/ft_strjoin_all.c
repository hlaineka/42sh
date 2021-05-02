/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:18:48 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/02 09:17:26 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_all(char *str1, char *str2, int mode)
{
	char	*returnable;
	int		i;
	int		w;

	returnable = ft_strnew(ft_strlen(str1) + ft_strlen(str2) + 1);
	i = 0;
	w = 0;
	while (str1 && str1[i])
		returnable[w++] = str1[i++];
	i = 0;
	while (str2 && str2[i])
		returnable[w++] = str2[i++];
	returnable[w] = '\0';
	if (mode == 1 || mode == 3)
		ft_free(str1);
	if (mode == 2 || mode == 3)
		ft_free(str2);
	return (returnable);
}
