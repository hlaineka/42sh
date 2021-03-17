/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:37:51 by helvi             #+#    #+#             */
/*   Updated: 2021/03/16 17:06:08 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"
# include "libft.h"

t_job		*parser(char *input)
{
	t_job	*returnable;
	t_token	*tokens;
	t_token	*temp;

	returnable = (t_job*)malloc(sizeof(t_job));
	ft_bzero(returnable, sizeof(t_job));
	tokens = lexer(input);
	temp = tokens;
	while (temp)
	{
		ft_printf("token: %i, value: %s. ", temp->token, temp->value);
		temp = temp->next;
	}
	returnable->command = ft_strdup(input);
	return(returnable);
}