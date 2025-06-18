/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:28:34 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/18 14:28:45 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_word_len(const char *line)
{
	int		i;
	char	quote_char;

	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
	{
		quote_char = line[i];
		i++;
		while (line[i] && line[i] != quote_char)
			i++;
		if (line[i] == quote_char)
			i++;
	}
	else
	{
		while (line[i] && !is_whitespace(line[i]) && !is_operator(line[i]))
			i++;
	}
	return (i);
}

int	handle_word_token(t_token **token_list, const char *line)
{
	int	len;

	len = get_word_len(line);
	append_token(token_list, line, len, TOKEN_WORD);
	return (len);
}