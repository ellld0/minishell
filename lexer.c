/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:38:24 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/23 12:02:24 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds a new token node at the end of the linked list.
void	add_token_back(t_token **list, t_token *new_node)
{
	t_token	*current;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

/*
** Creates a new token with the given type and a substring
** from the input line. The substring has length 'len'.
** It allocates memory for both the token and its value,
** copies the content from the input line, and appends
** the new token to the token list using add_token_back().
*/
int	append_token(t_token **list, const char *line, int len,
		t_token_type type)
{
	t_token	*new_node;
	char	*value;
	int		i;

	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (0);
	i = 0;
	while (i < len)
	{
		value[i] = line[i];
		i++;
	}
	value[i] = '\0';
	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		free(value);
		return (0);
	}
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	add_token_back(list, new_node);
	return (len);
}

/*
** Checks if the current line position starts with an operator.
** Supports both single-character operators ('<', '>', '|')
** and double-character operators ('<<', '>>').
** If an operator is found, the function creates a token
** of the correct type and length using append_token().
** Returns the number of characters consumed (1 or 2),
** or 0 if no operator was found.
*/
int	handle_operator_token(t_token **token_list, const char *line)
{
	if (line[0] == '<' && line[1] == '<')
		return (append_token(token_list, line, 2, TOKEN_HEREDOC));
	if (line[0] == '>' && line[1] == '>')
		return (append_token(token_list, line, 2, TOKEN_REDIR_APPEND));
	if (line[0] == '<')
		return (append_token(token_list, line, 1, TOKEN_REDIR_IN));
	if (line[0] == '>')
		return (append_token(token_list, line, 1, TOKEN_REDIR_OUT));
	if (line[0] == '|')
		return (append_token(token_list, line, 1, TOKEN_PIPE));
	return (0);
}

/*
** The main lexer function.
**
** This function takes the user's raw input line and converts it
** into a linked list of tokens (t_token). It loops through each
** character of the input line and classifies parts of the string
** into tokens like words, operators, and special symbols.
**
** Main steps:
** - Skip whitespace between tokens.
** - If the current character starts an operator (like '|', '<', '<<'),
**   it calls handle_operator_token() to create the correct token.
** - If the current character starts a word (command or argument),
**   it calls handle_word_token() to process and create a word token.
**
** The variable 'consumed' tracks how many characters each handler
** function consumes from the line, so we can move forward correctly.
** 
** If for any reason no characters were consumed (to avoid infinite loops),
** we manually advance 'i' by 1.
**
** The final result is a linked list of tokens, which the parser will
** later use to build a structured command tree for execution.
*/

t_token	*main_lexer(char *line)
{
	t_token	*token_list;
	int		i;
	int		consumed;

	token_list = NULL;
	i = 0;
	while (line[i])
	{
		consumed = 0;
		if (is_whitespace(line[i]))
		{
			i++;
			continue ;
		}
		else if (is_operator(line[i]))
			consumed = handle_operator_token(&token_list, &line[i]);
		else
			consumed = handle_word_token(&token_list, &line[i]);
		if (consumed == 0 && line[i])
			i++;
		else
			i += consumed;
	}
	return (token_list);
}
