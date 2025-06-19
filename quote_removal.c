/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:47 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/19 09:05:22 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* parser_utils.c                                     :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your-login <your-login@student.42.fr>      +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/06/18 18:50:11 by your-login        #+#    #+#             */
/* Updated: 2025/06/18 18:50:11 by your-login       ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

static void	process_quoted_len(const char *str, int *i, int *len)
{
	char	quote_char;

	quote_char = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote_char)
	{
		(*len)++;
		(*i)++;
	}
	if (str[*i] == quote_char)
		(*i)++;
}

static void	process_quoted_copy(const char *str, char *clean_str, int *i,
		int *j)
{
	char	quote_char;

	quote_char = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote_char)
	{
		clean_str[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str[(*i)] == quote_char)
		(*i)++;
}

static int	get_clean_len(const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			process_quoted_len(str, &i, &len);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(const char *str)
{
	char	*clean_str;
	int		i;
	int		j;

	clean_str = malloc(sizeof(char) * (get_clean_len(str) + 1));
	if (!clean_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			process_quoted_copy(str, clean_str, &i, &j);
		else
		{
			clean_str[j] = str[i];
			j++;
			i++;
		}
	}
	clean_str[j] = '\0';
	return (clean_str);
}
