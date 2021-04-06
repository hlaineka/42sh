/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:18:44 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/30 13:31:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		copy_envp(char **envp, t_term *term)
{
	int		i;

	i = 0;
	ft_bzero(term->envp, 1024);
	if (!envp)
		return (-1);
	while (envp[i])
	{
		term->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (0);
}
