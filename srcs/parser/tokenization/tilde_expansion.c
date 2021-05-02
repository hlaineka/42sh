/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:42:57 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/02 22:24:05 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include <pwd.h>

/*
** Tilde ~ parameter expansion. If there are characters between tilde and
** following dash /, those characters are interpreted to be a username, and
** the home directory is searched with getpwnam(). If tilde ~ is followed by
** dasd / (=~/), or if tilde is the ending character of the command word,
** homedirectory is searched from environment variables under the key HOME.
*/

static char	*get_user_homedir(t_token *tkn, int tilde, int end)
{
	char			*temp;
	struct passwd	*temp_pwd;
	char			*homedir;

	temp = ft_strsub_mid(tkn->value, tilde + 1, end);
	temp_pwd = getpwnam(temp);
	if (!temp_pwd)
	{
		ft_printf_fd(2, "username %s not found\n", temp);
		ft_free(temp);
		return (NULL);
	}
	homedir = temp_pwd->pw_dir;
	ft_strcut(tkn->value, tilde, end + 1);
	ft_free(temp);
	return (homedir);
}

int	tilde_expansion(t_token *tkn, t_term *term, int tilde)
{
	int				end;
	char			*homedir;

	if ((tilde != 0 && tkn->maintoken != tkn_assignment_word)
		|| tkn->quotes[tilde] != 0)
		return (0);
	end = tilde;
	while (tkn->value[end] && tkn->value[end] != '/')
		end++;
	if (end - tilde == 1)
	{
		homedir = ft_getenv("HOME", term->envp);
		if (!homedir)
			ft_printf_fd(2, "HOME not set\n");
		ft_strcut(tkn->value, tilde, tilde + 1);
	}
	else
		homedir = get_user_homedir(tkn, tilde, end);
	ft_printf(">>%s<<", tkn->value);
	ft_printf(">>%s<<", homedir);
	if (homedir == NULL)
		return (-1);
	tkn->value = ft_strpastei(tkn->value, homedir, tilde);
	add_quotearray(tkn);
	return (0);
}
