/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isarrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:12:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 11:48:28 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_up_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 65 && str[3] == 0)
		return (1);
	return (0);
}

int	ft_is_down_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 66 && str[3] == 0)
		return (1);
	return (0);
}

int	ft_is_right_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 67 && str[3] == 0)
		return (1);
	return (0);
}

int	ft_is_left_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 68 && str[3] == 0)
		return (1);
	return (0);
}
