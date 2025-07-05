/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:13 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/04 20:26:31 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **list_head, t_token *new_token)
{
	t_token	*current;

	if (!list_head || !new_token)
		return ;
	if (*list_head == NULL)
	{
		*list_head = new_token;
		return ;
	}
	current = *list_head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
}

int	handle_operator_token(t_token **list, const char *line)
{
	if (line[1] == line[0])
	{
		if (line[0] == '<')
			return (add_token_back(list, create_token("<<", TOKEN_HEREDOC)), 2);
		if (line[0] == '>')
			return (add_token_back(list, create_token(">>", TOKEN_REDIR_APPEND))
				, 2);
		if (line[0] == '&')
			return (add_token_back(list, create_token("&&", TOKEN_AND)), 2);
		if (line[0] == '|')
			return (add_token_back(list, create_token("||", TOKEN_OR)), 2);
	}
	if (line[0] == '|')
		return (add_token_back(list, create_token("|", TOKEN_PIPE)), 1);
	if (line[0] == '<')
		return (add_token_back(list, create_token("<", TOKEN_REDIR_IN)), 1);
	if (line[0] == '>')
		return (add_token_back(list, create_token(">", TOKEN_REDIR_OUT)), 1);
	if (line[0] == '(')
		return (add_token_back(list, create_token("(", TOKEN_LPAREN)), 1);
	if (line[0] == ')')
		return (add_token_back(list, create_token(")", TOKEN_RPAREN)), 1);
	return (0);
}

static int	get_word_len(const char *line)
{
	int		i;
	char	quote_char;

	i = 0;
	while (line[i] && !is_whitespace(line[i]) && !is_operator(line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_char = line[i];
			i++;
			while (line[i] && line[i] != quote_char)
				i++;
			if (line[i] == '\0')
			{
				printf("minishell: syntax error: unclosed quote\n");
				return (-1);
			}
			i++;
		}
		else if (line[i] == '\\' && line[i + 1])
			i += 2;
		else
			i++;
	}
	return (i);
}

int	handle_word_token(t_token **list, const char *line)
{
	int		len;
	char	*word;

	len = get_word_len(line);
	word = ft_substr(line, 0, len);
	if (!word)
		return (-1);
	add_token_back(list, create_token(word, TOKEN_WORD));
	free(word);
	return (len);
}
