/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:38:24 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/04 18:21:05 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_next_token(t_token **list_head, const char *line, int *i)
{
	int	len;

	if (is_whitespace(line[*i]))
	{
		(*i)++;
		return (0);
	}
	if (is_operator(line[*i]))
		len = handle_operator_token(list_head, &line[*i]);
	else
		len = handle_word_token(list_head, &line[*i]);
	if (len < 0)
		return (-1);
	*i += len;
	return (0);
}

t_token	*main_lexer(const char *line)
{
	t_token	*list_head;
	int		i;

	list_head = NULL;
	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (process_next_token(&list_head, line, &i) == -1)
		{
			free_token_list(list_head);
			return (NULL);
		}
	}
	return (list_head);
}
