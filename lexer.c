/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:38:24 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/18 14:43:04 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
