/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:59:34 by helvi             #+#    #+#             */
/*   Updated: 2021/03/17 09:34:40 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"
# include "libft.h"

bool		check_quotes(t_token *current, char c, bool *single_quoted, bool *double_quoted)
{
	if (c == 34)
	{
		current->double_quoted = TRUE;
		*double_quoted = !*double_quoted;
	}
	if (c == 44)
	{
		current->single_quoted = TRUE;
		*single_quoted = !*single_quoted;
	}
	return (TRUE);
}

bool		get_tokenstr(t_token **current, char *delimiters, char **source)
{
	int		i;
	bool	single_quoted;
	bool	double_quoted;

	if (*source == NULL || source[0][0] == '\0')
	{
		ft_free(*current);
		return (FALSE);
	}
	i = 0;
	(*current)->single_quoted = FALSE;
	(*current)->double_quoted = FALSE;
	single_quoted = FALSE;
	double_quoted = FALSE;
	while (source[0][i])
	{
		check_quotes(*current, source[0][i], &single_quoted, &double_quoted);
		if (!single_quoted && double_quoted && ft_strchr(delimiters, source[0][i]))
		{
			if (ft_strchr(OPCHARS, source[0][i]))
				(*current)->value = ft_strsub(*source, 0, i + 1);
			else
				(*current)->value = ft_strsub(*source, 0, i);
			if (!(*current)->value || (*current)->value[0] == '\0')
			{
				*source = *source + 1;
				ft_free((*current)->value);
				continue;
			}
			*source = *source + i + 1;
			return(TRUE);
		}
		i++;
	}
	(*current)->value = ft_strsub(*source, 0, i);
	*source = *source + i;
	return(TRUE);
}

t_token				*get_token(char *delimiters, char **source)
{
	t_token	*current;
	
	current = (t_token*)malloc(sizeof(t_token));
	ft_bzero(current, sizeof(t_token));
	if (!get_tokenstr(&current, delimiters, source))
		return (current);
	return(current);
}