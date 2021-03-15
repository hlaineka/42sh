/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:37:51 by helvi             #+#    #+#             */
/*   Updated: 2021/03/14 15:23:29 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

t_job		*parser(char *input)
{
	t_job	*returnable;
	t_list	*tokens;
	t_token	*temp;

	returnable = NULL;
	tokens = lexer(input);
	while (tokens)
	{
		temp = (t_token*)tokens->content;
		ft_printf("%s ", temp->value);
	}
	returnable->command = ft_strdup(input);
	return(returnable);
}