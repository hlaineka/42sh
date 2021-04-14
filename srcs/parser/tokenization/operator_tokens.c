/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:57:08 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/12 10:25:07 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char	*ft_strcut(char *str, int start, int end)
{
	char	*returnable;
	int		i;
	int		w;

	returnable = malloc(end - start + 1);
	i = start;
	w = 0;
	while (i < end)
	{
		returnable[w] = str[i];
		w++;
		i++;
	}
	returnable[w] = '\0';
	i = 0;
	while (str[end + i])
	{
		str[start + i] = str[end + i];
		i++;
	}
	while (i <= (end - start))
	{
		str[start + i] = '\0';
		i++;
	}
	return (returnable);
}

int	handle_tkn_io_number(t_token *current)
{
	int		i;
	t_token	*new_subtoken;

	i = 0;
	while (current->value[i] && ft_isdigit(current->value[i]))
		i++;
	if (!ft_strchr(OPCHARS, current->value[i]))
		return (-1);
	if (i > 0)
	{
		new_subtoken = init_token();
		new_subtoken->maintoken = tkn_io_number;
		new_subtoken->value = ft_strcut(current->value, 0, i);
	}
	return (0);
}

int	handle_redirection_op(t_token *current)
{
	if (ft_strlen(current->value) > 3)
		return (-1);
	else if (ft_strequ(current->value, "<"))
		current->maintoken = tkn_less;
	else if (ft_strequ(current->value, ">"))
		current->maintoken = tkn_great;
	else if (ft_strequ(current->value, "<<"))
		current->maintoken = tkn_dless;
	else if (ft_strequ(current->value, ">>"))
		current->maintoken = tkn_dgreat;
	else if (ft_strequ(current->value, "<&"))
		current->maintoken = tkn_lessand;
	else if (ft_strequ(current->value, ">&"))
		current->maintoken = tkn_greatand;
	else if (ft_strequ(current->value, "<>"))
		current->maintoken = tkn_lessgreat;
	else if (ft_strequ(current->value, "<<-"))
		current->maintoken = tkn_dlessdash;
	else if (ft_strequ(current->value, ">|"))
		current->maintoken = tkn_clobber;
	return (0);
}

int	handle_operation(t_token *current)
{
	if (ft_strequ(current->value, "|"))
		current->maintoken = tkn_pipe;
	else if (ft_strequ(current->value, "&"))
		current->maintoken = tkn_and;
	else if (ft_strequ(current->value, ";"))
		current->maintoken = tkn_semi;
	else if (ft_strequ(current->value, "&&"))
		current->maintoken = tkn_and_if;
	else if (ft_strequ(current->value, "||"))
		current->maintoken = tkn_or_if;
	else if (ft_strequ(current->value, "!"))
		current->maintoken = tkn_bang;
	else if (ft_strequ(current->value, ";;"))
		current->maintoken = tkn_dsemi;
	else if (current->maintoken == tkn_operator || current->maintoken == tkn_redirop)
		return (-1);
	return (0);
}

int	handle_basic_optkn(t_token *current)
{
	if (-1 == handle_tkn_io_number(current))
		return -1;
	if (-1 == handle_redirection_op(current))
		return (-1);
	if (-1 == handle_operation(current))
		return (-1);
	return (0);
}

t_token	*validate_operator_tokens(t_token *first)
{
	t_token	*current;

	if (!first)
		return (NULL);
	current = first;
	while (current)
	{
		if (current->maintoken != tkn_word)
		{	
			if (-1 == handle_basic_optkn(current))
			{
				ft_printf_fd(2, "syntax error near token %s\n", current->value);
				free_tokens(first);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (first);
}
