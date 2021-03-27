/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:00:19 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 11:28:31 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INCLUDES_H
# define FT_INCLUDES_H

# include <curses.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# include "libft.h"
# include "structs_21.h"
# include "input.h"
# include "parser.h"
# include "ft_signal.h"

int 				g_ft_errno;

#endif
