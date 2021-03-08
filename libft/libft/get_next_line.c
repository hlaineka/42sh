/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:12:13 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/02/21 09:50:21 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_read_fd(const int fd, char **str)
{
	int		rt;
	char	buff[BUFF_SIZE + 1];
	char	*str_temp;

	rt = 0;
	if (!str[fd] && (rt = read(fd, buff, BUFF_SIZE)))
	{
		if (rt == -1)
			return (rt);
		buff[rt] = '\0';
		str[fd] = ft_strdup(buff);
	}
	if (rt == 0 && !str[fd])
		return (0);
	while (!ft_strchr(str[fd], '\n') && (rt = read(fd, buff, BUFF_SIZE)))
	{
		if (rt == -1)
			return (rt);
		buff[rt] = '\0';
		str_temp = ft_strjoin(str[fd], buff);
		ft_strdel(&str[fd]);
		str[fd] = str_temp;
	}
	return (rt);
}

static int		ft_crop_to_line(const int fd, int rt, char **str, char **line)
{
	char	*ptr_t;

	if (rt == 0 && str[fd] && str[fd][0] == '\0')
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		return (0);
	}
	if (rt == 0 && str[fd] && !ft_strchr(str[fd], '\n'))
	{
		*line = ft_strdup(str[fd]);
		str[fd][0] = '\0';
		return (1);
	}
	if (str[fd] && ft_strchr(str[fd], '\n'))
	{
		*line = ft_strsub(str[fd], 0, (ft_strchr(str[fd], '\n') - str[fd]));
		ptr_t = str[fd];
		str[fd] = ft_strdup(ft_strchr(str[fd], '\n') + 1);
		ft_strdel(&ptr_t);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str[MAX_FD];
	int				rt;

	if (fd < 0 || fd > MAX_FD || BUFF_SIZE < 1 || !line)
		return (-1);
	rt = ft_read_fd(fd, str);
	if (rt == -1)
		return (-1);
	return (ft_crop_to_line(fd, rt, str, line));
}
