/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:10:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/18 15:22:59 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int				print_prompt(int mode)
{
	if (mode == PROMPT_NORMAL)
		return (ft_printf_fd(STDOUT_FILENO, "$> "));
	if (mode == PROMPT_QUOTE)
		return (ft_printf_fd(STDOUT_FILENO, "quote> "));
	if (mode == PROMPT_DQUOTE)
		return (ft_printf_fd(STDOUT_FILENO, "dquote> "));
	if (mode == PROMPT_BQUOTE)
		return (ft_printf_fd(STDOUT_FILENO, "bquote> "));
	if (mode == PROMPT_ESCAPECHAR)
		return (ft_printf_fd(STDOUT_FILENO, "> "));
	return (ft_printf_fd(STDOUT_FILENO, "$> "));
}
