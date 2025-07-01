/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:50:39 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 12:58:50 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_expanded_len(const char *str)
{
	int		i;
	int		len;
	char	*status_str;
	int		in_single_quote;

	i = 0;
	len = 0;
	in_single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		if (str[i] == '$' && str[i + 1] == '?' && !in_single_quote)
		{
			status_str = ft_itoa(get_exit_status());
			len += ft_strlen(status_str);
			free(status_str);
			i++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

static void	perform_expansion(char *new_str, const char *old_str)
{
	int		i;
	int		j;
	char	*status_str;
	int		in_single_quote;

	i = 0;
	j = 0;
	in_single_quote = 0;
	while (old_str[i])
	{
		if (old_str[i] == '\'')
			in_single_quote = !in_single_quote;
		if (old_str[i] == '$' && old_str[i + 1] == '?' && !in_single_quote)
		{
			status_str = ft_itoa(get_exit_status());
			ft_strcpy(&new_str[j], status_str);
			j += ft_strlen(status_str);
			free(status_str);
			i++;
		}
		else
			new_str[j++] = old_str[i];
		i++;
	}
	new_str[j] = '\0';
}

char	*expand_status_variable(char *str)
{
	char	*expanded_str;
	int		expanded_len;

	expanded_len = get_expanded_len(str);
	expanded_str = malloc(sizeof(char) * (expanded_len + 1));
	if (!expanded_str)
		return (NULL);
	perform_expansion(expanded_str, str);
	return (expanded_str);
}
