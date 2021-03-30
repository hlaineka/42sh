/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:37:51 by helvi             #+#    #+#             */
/*   Updated: 2021/03/29 15:36:39 by hlaineka         ###   ########.fr       */
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

static void		debug_print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		ft_printf("token: %i, value: %s. ", temp->maintoken, temp->value);
		temp = temp->next;
		ft_printf("\n");
	}
	ft_printf("\n");
}

static void		debug_print_tree(t_node *node)
{
	if (!node)
		return;
	
	if (node->left)
	{
		ft_printf("parent: %s, left %s. ", node->command, node->left->command);
		debug_print_tree(node->left);
	}
	if (node->right)
	{
		ft_printf("parent: %s, right %s. ", node->command, node->right->command);
		debug_print_tree(node->right);
	}
}

t_node		*parser(char *input, bool debug)
{
	t_token	*tokens;
	t_node	*root;

	tokens = lexer(input);
	//alias handling call
	//reserved words recognition call
	//positional parameteres check call
	//special parameters and substitution, word expansions
	//field splitting = extra empty character removal that came from expansions & aliases
	//pathname extensions
	quote_removal(tokens);
	//redirection (marking or handling?)
	if (debug)
		debug_print_tokens(tokens);
	root = ast_creator(tokens, debug);
	if (debug)
		debug_print_tree(root);
	//free_tokens(tokens);
	return(root);
}