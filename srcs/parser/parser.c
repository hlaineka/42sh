/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:37:51 by helvi             #+#    #+#             */
/*   Updated: 2021/03/18 21:30:39 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"
# include "libft.h"

char		*remove_chars(char *str, int c)
{
	char	*returnable;
	int		i;
	int		w;

	returnable = ft_strnew(ft_strlen(str));
	i = -1;
	w = 0;
	while (str[++i])
	{
		if (str[i] == c)
			continue;
		returnable[w] = str[i];
		w++;
	}
	returnable[w] = '\0';
	return (returnable);
}

void		quote_removal(t_token *first)
{
	t_token *temp;
	char	*temp_str;

	temp = first;
	temp_str = NULL;
	while(first)
	{
		if (temp->single_quoted)
		{
			temp_str = remove_chars(temp->value, 39);
			ft_free(temp->value);
			temp->value = ft_strdup(temp_str);
			ft_free(temp_str);
		}
		if (temp->double_quoted)
		{
			temp_str = remove_chars(temp->value, 34);
			ft_free(temp->value);
			temp->value = ft_strdup(temp_str);
			ft_free(temp_str);
		}
		first = first->next;
	}
}

t_job		*parser(char *input)
{
	t_job	*returnable;
	t_token	*tokens;
	t_token	*temp;

	tokens = lexer(input);
	//alias handling call
	//reserved words recognition call
	//positional parameteres check call
	//special parameters and substitution, word expansions
	//field splitting = extra empty character removal that came from expansions & aliases
	//pathname extensions
	quote_removal(tokens);
	//redirection (marking or handling?)
	temp = tokens;
	while (temp)
	{
		ft_printf("token: %i, value: %s. ", temp->maintoken, temp->value);
		temp = temp->next;
	}
	tree_maker(tokens);
	returnable = (t_job*)malloc(sizeof(t_job));
	ft_bzero(returnable, sizeof(t_job));
	returnable->command = ft_strdup(input);
	return(returnable);
}