/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:22:42 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/12 11:58:25 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_char(const char *src, char *dest, t_quote_state *s)
{
	if (src[s->i] == '\\' && s->quote_char != '\'')
	{
		if (src[s->i + 1])
		{
			s->i++;
			dest[s->j++] = src[s->i];
		}
		else
			dest[s->j++] = src[s->i];
	}
	else if (src[s->i] == '\'' || src[s->i] == '\"')
	{
		if (s->quote_char == 0)
			s->quote_char = src[s->i];
		else if (s->quote_char == src[s->i])
			s->quote_char = 0;
		else
			dest[s->j++] = src[s->i];
	}
	else
		dest[s->j++] = src[s->i];
}

char	*remove_quotes(char *str)
{
	char			*new_str;
	t_quote_state	state;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	state.quote_char = 0;
	state.i = 0;
	state.j = 0;
	while (str[state.i])
	{
		process_char(str, new_str, &state);
		state.i++;
	}
	new_str[state.j] = '\0';
	return (new_str);
}
