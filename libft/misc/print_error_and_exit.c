/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:35:24 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/06 13:41:30 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h> // perror needs this. do we need this?

void	print_error_and_exit(char *name)
{
	ft_printf("ft_ls: %s: ", name);
	perror("");
	exit(0);
}
