/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:13 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/05 11:14:44 by sdavi-al         ###   ########.fr       */
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

static int	skip_quoted_part(const char *line, int i)
{
	char	quote_char;

	quote_char = line[i];
	i++;
	while (line[i])
	{
		if (line[i] == quote_char)
			break ;
		if (quote_char == '\"' && line[i] == '\\' && line[i + 1])
			i += 2;
		else
			i++;
	}
	if (line[i] != quote_char)
		return (printf("minishell: syntax error: unclosed quote\n"), -1);
	return (i + 1);
}

static int	get_word_len(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_whitespace(line[i]) && !is_operator(line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = skip_quoted_part(line, i);
			if (i == -1)
				return (-1);
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
