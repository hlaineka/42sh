/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:11:26 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/29 13:44:45 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "includes.h"
# include <stdbool.h>

/*
** When there are two plain words one after another, a delimiter token needs to be
** added to make sure the bind together in the shunting yard algorithm.
*/

t_token		*add_delimiter_token(t_token *tkn)
{
	t_token *new;
	
	new = (t_token*)malloc(sizeof(t_token));
	ft_bzero(new, sizeof(t_token));
	new->single_quoted = FALSE;
	new->double_quoted = FALSE;
	new->precedence = 5;
	tkn->next->prev = new;
	new->next = tkn->next;
	tkn->next = new;
	new->prev = tkn;
	return (new);
}

t_token		*add_precedence(t_token *first)
{
	t_token	*temp;
	t_token *returnable;

	temp = first;
	returnable = first;
	while(temp)
	{
		if (temp->maintoken == tkn_word && temp->next && temp->next->maintoken == tkn_word)
			temp = add_delimiter_token(temp);
		else if (temp->maintoken == tkn_less || temp->maintoken == tkn_great
		|| temp->maintoken == tkn_less || temp->maintoken == tkn_great
		|| temp->maintoken == tkn_lessand || temp->maintoken == tkn_greatand
		|| temp->maintoken == tkn_lessgreat || temp->maintoken == tkn_dlessdash
		|| temp->maintoken == tkn_clobber)
			temp->precedence = 4;
		else if (temp->maintoken == tkn_pipe)
			temp->precedence = 3;
		else if (temp->maintoken == tkn_and_if || temp->maintoken == tkn_or_if)
			temp->precedence = 2;
		else if (temp->maintoken == tkn_semi || temp->maintoken == tkn_and)
			temp->precedence = 1;
		if (temp->maintoken == tkn_pipe || temp->maintoken == tkn_and_if || temp->maintoken == tkn_or_if)
			temp->left_associative = TRUE;
		else
			temp->left_associative = FALSE; //I think this can be left out when initialized as zero
		temp = temp->next;
	}
	return (returnable);
}

t_token		*push_to_output(t_token **op_stack, t_token **word_stack, t_token *output)
{
	t_token	*temp;
	t_token	*returnable;
	
	returnable = output;
	ft_printf("push to output: ");
	while (*word_stack)
	{
		ft_printf("%s ", (*word_stack)->value);
		temp = (*word_stack)->prev;
		returnable = push_to_end(*word_stack, returnable);
		*word_stack = temp;
	}
	if (*op_stack)
	{
		ft_printf("%s \n", (*op_stack)->value);
		temp = (*op_stack)->prev;
		returnable = push_to_end((*op_stack), returnable);
		*op_stack = temp;
	}
	return (returnable);
}

//funtions need to be added separately. They will need their own token.

t_token		*handle_operator(t_token **op_stack, t_token **word_stack, t_token **input, t_token *output)
{
	t_token *returnable;

	returnable = output;
	if ((*input)->maintoken == tkn_lpar)
	{
		ft_printf("left paranthesis\n");
		*op_stack = push_to_front(*input, *op_stack);
	}
	else if ((*input)->maintoken == tkn_rpar)
	{
		ft_printf("right paranthesis\n");
		while (*op_stack && (*op_stack)->maintoken != tkn_lpar)
		{
			returnable = push_to_output(op_stack, word_stack, returnable);
		}
		if (!(*op_stack))
		{
			ft_printf_fd(2, "syntax error, wrong amount of paranthesis");
			return (NULL);
		}
		*input = delete_token(*input);
		*op_stack = delete_token(*op_stack);
	}
	else
	{
		ft_printf("handle other operators than paranthesis\n");
		while (*op_stack && ((*op_stack)->precedence > (*input)->precedence || ((*op_stack)->precedence == (*input)->precedence && (*input)->left_associative)))
		{	
			ft_printf("in while, pushing from op_stack to output. %s\n", (*op_stack)->value);
			returnable = push_to_output(op_stack, word_stack, returnable);
		}
		ft_printf("Pushing from input to op_stack.");
		if (*input)
			ft_printf("%s", (*input)->value);
		ft_printf("\n");
		*op_stack = push_to_front(*input, *op_stack);
	}
	return(returnable);
}

t_token		*shunting_yard(t_token *first)
{
	t_token	*op_stack;
	t_token *word_stack;
	t_token	*output;
	t_token	*input;
	t_token *temp;

	temp = NULL;
	op_stack = NULL;
	output = NULL;
	word_stack = NULL;
	input = first;
	while (input)
	{
		temp = input->next;
		//ft_printf("read new token\n");
		if (input->precedence == 0)
		{
			ft_printf("add tkn_word to word_stack\n");
			word_stack = push_to_front(input, word_stack);
		}
		else
		{	
			ft_printf("handle operator\n");
			output = handle_operator(&op_stack, &word_stack, &input, output);
		}
		//if (output == NULL)
		//{
		//	ft_printf("output in NULL\n");
		//	return (NULL);
		//}
		input = temp;
	}
	output = push_to_output(&op_stack, &word_stack, output);
	while (op_stack)
	{
		temp = op_stack->prev;
		//ft_printf("push rest of the op_stack to output\n");
		push_to_end(op_stack, output);
		op_stack = temp;
	}
	return (output);
}

static void	debug_printing(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	ft_printf("print precedence:\n");
	while (temp)
	{
		ft_printf("precedence: %i, value: %s. ", temp->precedence, temp->value);
		temp = temp->next;
		ft_printf("\n");
	}
	ft_printf("\n");
}

t_node	*init_node()
{
	t_node	*returnable;

	//copy std:s here
	returnable = malloc(sizeof(t_node));
	ft_bzero(returnable, sizeof(t_node));
	returnable->parent = NULL;
	returnable->left = NULL;
	returnable->right = NULL;
	returnable->command = NULL;
	returnable->envp = malloc(ARGV_SIZE);
	//copy envp
	returnable->argv = malloc(ARGV_SIZE);
	return(returnable);
}

int		push_word(t_token *tkn, t_node **node_stack)
{
	int 	i;
	t_node	*new_node;

	i = 0;
	while(node_stack[i] && i < 30)
		i++;
	if (i == 30)
	{
		ft_printf_fd(2, "node stack full");
		return (-1);
	}
	new_node = init_node();
	new_node->command = ft_strdup(tkn->value);
	ft_printf("adding leaf node: %s. ", new_node->command);
	delete_token(tkn);
	node_stack[i] = new_node;
	return (0);
}

char	**combine_argvs(char **dest, char **argv1, char **argv2)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (argv1 && argv1[i])
	{
		dest[w] = ft_memcpy(dest[w], argv1[i], ft_strlen(argv1[i]));
		i++;
		w++;
	}
	i = 0;
	while (argv2 && argv2[i])
	{
		dest[w] = ft_memcpy(dest[w], argv2[i], ft_strlen(argv2[i]));
		i++;
		w++;
	}
	return (dest);
}

int		push_operator(t_token *tkn, t_node **node_stack)
{
	int 	i;
	t_node	*new_node;

	i = 0;
	while(node_stack[i] && i < 30)
		i++;
	if (i == 30)
	{
		ft_printf_fd(2, "node stack full");
		return (-1);
	}
	new_node = init_node();
	new_node->command = ft_strdup(tkn->value);
	new_node->left = node_stack[--i];
	node_stack[i]->parent = new_node;
	if (i > 0)
	{
		node_stack[i] = NULL;
		i--;
		new_node->right = node_stack[i];
		node_stack[i]->parent = new_node;
	}
	node_stack[i] = NULL;
	ft_printf("adding operator node: %s , ", new_node->command);
	ft_printf("left: ");
	if (new_node->left)
		ft_printf("%s", new_node->left->command);
	ft_printf(", right: ");
	if (new_node->right)
		ft_printf("%s", new_node->right->command);
	ft_printf(". ");
	node_stack[i] = new_node;
	return (0);
}

t_node		*ast_creator(t_token *first, bool debug)
{
	t_token	*new_first;
	t_token	*temp;
	t_node	*root;
	t_node	*node_stack[30];

	if (!first)
		return (NULL);
	root = NULL;
	ft_bzero(node_stack, sizeof(t_node*) * 30);
	new_first = add_precedence(first);
	if (debug)
		debug_printing(new_first);
	new_first = shunting_yard(first);
	while (new_first)
	{
		temp = new_first->next;
		if (new_first->precedence == 0)
		{
			ft_printf("push word. ");
			if (-1 == (push_word(new_first, node_stack)))
				return (NULL);
		}
		else
		{
			ft_printf("push operator. ");
			push_operator(new_first, node_stack);
		}
		new_first = temp;
	}
	if (node_stack[1])
	{
		ft_printf_fd(2, "syntax error");
		return(NULL);
	}
	root = node_stack[0];
	return (root);
}