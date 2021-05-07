/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isshiftarrows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:12:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/07 11:41:07 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_shift_up_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 49 && str[3] == 59
		&& str[4] == 50 && str[5] == 65 && str[6] == 0)
		return (1);
	return (0);
}

int	ft_is_shift_down_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 49 && str[3] == 59
		&& str[4] == 50 && str[5] == 66 && str[6] == 0)
		return (1);
	return (0);
}

int	ft_is_shift_right_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 49 && str[3] == 59
		&& str[4] == 50 && str[5] == 67 && str[6] == 0)
		return (1);
	return (0);
}

int	ft_is_shift_left_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 49 && str[3] == 59
		&& str[4] == 50 && str[5] == 68 && str[6] == 0)
		return (1);
	return (0);
}
