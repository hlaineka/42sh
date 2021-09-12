/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 20:35:23 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/11 17:17:50 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** return 0 if there is no = sign in the src, otherwise writes the value and
** name to stirngs allocated by the caller.
*/

int	get_name_and_value(char *src, char *value, char *name)
{
	int		i;
	int		w;

	i = 0;
	while (src[i] != '\0' && src[i] != '=')
	{
		name[i] = src[i];
		i++;
	}
	if (src[i] == '\0')
		return (0);
	name[i++] = '\0';
	w = 0;
	while (src[i] != '\0')
		value[w++] = src[i++];
	value[w] = '\0';
	return (1);
}
