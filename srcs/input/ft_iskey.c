/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iskey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:12:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/22 10:16:57 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_home_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 72 && str[3] == 0)
		return (1);
	return (0);
}

int		ft_is_end_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 70 && str[3] == 0)
		return (1);
	return (0);
}

int		ft_is_altx_key(char *str)
{
	if (str[0] == -30 && str[1] == -119 && str[2] == -120 && str[3] == 0)
		return (1);
	return (0);
}

int		ft_is_altc_key(char *str)
{
	if (str[0] == -61 && str[1] == -89 && str[2] == 0)
		return (1);
	return (0);
}

int		ft_is_altv_key(char *str)
{
	if (str[0] == -30 && str[1] == -120 && str[2] == -102 && str[3] == 0)
		return (1);
	return (0);
}
