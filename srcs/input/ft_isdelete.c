/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdelete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:12:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 11:48:47 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_delete_key(char *str)
{
	if (str[0] == 27 && str[1] == 91 && str[2] == 51 && str[3] == 126)
		return (1);
	return (0);
}
