/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:57:08 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/14 18:07:30 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char	*ft_strcut(char *str, int start, int end)
{
	char	*returnable;
	int		i;
	int		w;
	int		len;

	returnable = malloc(end - start + 1);
	len = ft_strlen(str);
	i = start;
	w = 0;
	while (i < end)
	{
		returnable[w] = str[i];
		w++;
		i++;
	}
	returnable[w] = '\0';
	i = start;
	w = end;
	while (str[w])
	{
		str[i] = str[w];
		i++;
		w++;
	}
	while (i <= len)
		str[i++] = '\0';
	return (returnable);
}

int	handle_tkn_io_number(t_token *current)
{
	int		i;
	t_token	*new_subtoken;

	i = 0;
	new_subtoken = NULL;
	while (current->value[i] && ft_isdigit(current->value[i]))
		i++;
	if (!ft_strchr(OPCHARS, current->value[i]))
		return (-1);
	if (i > 0)
	{
		new_subtoken = init_token();
		new_subtoken->maintoken = tkn_io_number;
		new_subtoken->value = ft_strcut(current->value, 0, i);
		add_subtoken(current, new_subtoken);
	}
	return (0);
}

int	handle_redirection_op(t_token *current)
{
	if (ft_strlen(current->value) > 4)
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
	int	returnable;

	returnable = 0;
	returnable = handle_tkn_io_number(current);
	if (returnable != -1)
		returnable = handle_redirection_op(current);
	if (returnable != -1)
		returnable = handle_operation(current);
	return (returnable);
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
