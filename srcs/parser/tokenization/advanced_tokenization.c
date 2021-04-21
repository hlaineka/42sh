/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_tokenization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:01:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/21 09:52:51 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include <pwd.h>

int	tilde_expansion(t_token *tkn, t_term *term, int tilde)
{
	int				end;
	char			*homedir;
	char			*temp;
	struct passwd	*temp_pwd;
	
	if ((tilde != 0 && tkn->maintoken != tkn_assignment_word) || tkn->quotes[tilde] != 0)
		return (0);
	end = tilde;
	while (tkn->value[end] && tkn->value[end] != '/')
		end++;
	if (end - tilde > 1)
	{
		temp = ft_strsub_mid(tkn->value, tilde + 1, end);
		temp_pwd = getpwnam(temp);
		if (!temp_pwd)
		{
			ft_printf_fd(2, "username %s not found\n", temp);
			ft_free(temp);
			return (-1);
		}
		homedir = ft_strdup(temp_pwd->pw_dir);
		ft_free(temp);
	}
	else	
		homedir = ft_getenv("HOME", term->envp);
	if (homedir == NULL)
	{
		ft_printf_fd(2, "HOME not set\n");
		return (-1);
	}
	ft_printf(homedir);
	temp = ft_replc(tkn->value, tilde, homedir);
	ft_printf(temp);
	ft_free(tkn->value);
	tkn->value = temp;
	add_quotearray(tkn);
	return (0);
}

char	*ft_strpastei(char *dest, char *new, int i)
{
	char	*returnable;
	int		w;
	int		o;

	returnable = ft_strnew(ft_strlen(dest) + ft_strlen(new) + 1);
	w = 0;
	while (w <= i && dest && dest[w])
	{
		returnable[w] = dest[w];
		w++;
	}
	o = 0;
	while (new && new[o])
		returnable[w++] = new[o++];
	while (dest && dest[i])
		returnable[w++] = dest[i++];
	returnable[w] = '\0';
	ft_free(dest);
	return (returnable);
}	

int	dollar_parameter(t_token *tkn, t_term *term, int start)
{
	int 	end;
	char	*parameter;
	char	*substitution;

	end = start;
	while (tkn->value[end])
	{
		if (tkn->value[end] == '}' && tkn->quotes[end] == 0)
			break;
		end++;
	}
	if (tkn->value[end] != '}' || tkn->quotes[end] != 0)
	{
		ft_printf_fd(2, "syntax error near token $");
		return (-1);
	}
	parameter = ft_strsub_mid(tkn->value, start, end);
	if (ft_strequ(parameter, "?"))
		substitution = ft_itoa(term->last_return);
	else	
		substitution = ft_getenv(parameter, term->envp);
	ft_strcut(tkn->value, start - 2, end + 1);
	tkn->value = ft_strpastei(tkn->value, substitution, start - 2);
	ft_free(parameter);
	add_quotearray(tkn);
	return (1);
}

int	dollar_expansion(t_token *tkn, t_term *term, int dollar)
{
	if (tkn->quotes[dollar] != 0)
		return (0);
	if (tkn->value[dollar + 1] == '{' && tkn->quotes[dollar + 1] == 0)
	{	
		if (-1 == dollar_parameter(tkn, term, dollar + 2))
			return (-1);
	}
	//else if (tkn->value[dollar + 1] == '(' && tkn->quotes[dollar + 1] == 0)
	//	command_substitution(tkn, term, dollar + 2);
	else
		return (0);
	return (0);
}

int	token_value_expansion(t_token *tkn, t_term *term)
{
	int		i;
	
	i = 0;
	while(tkn->value && tkn->value[i])
	{
		if (tkn->value[i] == '~' && -1 == tilde_expansion(tkn, term, i))
			return (-1);
		if (tkn->value[i] == '$' && -1 == dollar_expansion(tkn, term, i))
			return (-1);
		i++;
	}
	return (0);
}

t_token *word_expansions(t_token *first, t_term *term)
{
	t_token *temp;
	t_token	*temp_sub;

	temp = first;
	while (temp)
	{
		if (-1 == token_value_expansion(temp, term))
		{
			free_tokens(first);
			return (NULL);
		}
		temp_sub = temp->subtokens;
		while(temp_sub)
		{
			if (-1 == token_value_expansion(temp_sub, term))
			{
				free_tokens(first);
				return (NULL);
			}
			temp_sub = temp_sub->next;
		}
		temp = temp->next;
	}
	return (first);
}

t_token	*advanced_tokenization(t_token *first, t_term *term)
{
	//assignment_words
	//alias handling call
	//reserved words recognition call
	//positional parameteres check call
	//special parameters and substitution, word expansions
	first = word_expansions(first, term);
	//field splitting = extra empty character removal that came from expansions & aliases
	//pathname extensions
	return (first);
}