/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:12:09 by helvi             #+#    #+#             */
/*   Updated: 2021/05/02 11:24:32 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <signal.h>
# include "includes.h"

void	start_signal(void);
void	set_signal_input(void);
void	sig_handler_input(int signo);
void	sig_handler_exec(int signo);
void	signals_to_default(void);
void	sig_child_handler(void);

#endif
