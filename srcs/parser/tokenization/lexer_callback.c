/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_callback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 21:43:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/03 21:44:10 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	lexer_callback(t_token **temp, t_token **command_first,
	t_term *term, t_token *(*callback)(t_token **, t_term *, t_token **))
{
	*command_first = callback(command_first, term, temp);
	*temp = *command_first;
}

