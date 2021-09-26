/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autotest.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 16:35:57 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 08:09:55 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOTEST_H
# define AUTOTEST_H

static const char	*g_autotest[] = {
	"echo 'ls\n' >> testresult",
	"ls >> testresult",
	"echo '\n--------------------------------\n ls -laF\n' >> testresult",
	"ls -laF >> testresult",
	"echo '\n--------------------------------\n ls -l a F\n' >> testresult",
	"ls -l -a -F >> testresult",
	NULL
};

#endif
