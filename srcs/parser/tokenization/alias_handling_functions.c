/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handling_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 12:17:39 by hlaineka          #+#    #+#             */
/*   Updated: 2021/10/02 12:24:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"
#include "includes.h"

t_token	*substitute_token(t_token *first, t_token *new,
	t_token *current)
{
	t_token	*prev;
	t_token	*next;
	t_token	*returnable;

	returnable = first;
	prev = current->prev;
	next = current->next;
	free_tokens(&(current->subtokens));
	free_token(&current);
	if (prev)
		prev->next = new;
	else if (new)
		returnable = new;
	else
		returnable = next;
	if (new)
	{
		new->prev = prev;
		while (new->next)
			new = new->next;
		new->next = next;
	}
	if (next)
		next->prev = new;
	return (returnable);
}

int	check_and_add_alias(char **orig_commands, t_alias *a, int *first_word)
{
	int	i;

	i = 0;
	while (orig_commands[i])
	{
		if (ft_strequ(orig_commands[i], a->value))
			return (-1);
		i++;
	}
	orig_commands[i] = ft_strdup(a->value);
	if (a && a->value && a->value[0]
		&& (a->value[ft_strlen(a->value) - 1] == ' '
			|| a->value[ft_strlen(a->value) - 1] == '\t'
			|| a->value[ft_strlen(a->value) - 1] == '\n'))
		*first_word = 2;
	else
		*first_word = 0;
	return (0);
}

int	init_check_first_word(char ***oc, t_token *temp)
{
	*oc = malloc(sizeof(char *) * STR_LENGTH);
	ft_bzero((void *)(*oc), (sizeof(char *) * STR_LENGTH));
	oc[0][0] = ft_strdup(temp->value);
	return (1);
}

t_token	*parse_new_command(t_alias *a, t_term *term, t_token **first,
	t_token **temp)
{
	t_token	*new;

	if (!a->value[0])
		a->value = ft_strdup(" ");
	new = lexer(ft_strdup(a->value), term, 0);
	*first = substitute_token(*first, new, *temp);
	return (new);
}
