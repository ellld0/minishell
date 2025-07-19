/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:22:42 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 12:43:42 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote_character(const char *src, char *dest,
		t_quote_state *s)
{
	if (s->quote_char == 0)
	{
		s->quote_char = src[s->i];
	}
	else if (s->quote_char == src[s->i])
	{
		s->quote_char = 0;
	}
	else
	{
		dest[s->j] = src[s->i];
		s->j++;
	}
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
		if (str[state.i] == '\'' || str[state.i] == '\"')
			handle_quote_character(str, new_str, &state);
		else
		{
			new_str[state.j] = str[state.i];
			state.j++;
		}
		state.i++;
	}
	new_str[state.j] = '\0';
	return (new_str);
}
