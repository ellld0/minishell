/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:50:39 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 18:46:48 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_var_value(char *new_str, int *j, const char *old_str, int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(&old_str[*i + 1]);
	if (var_name)
	{
		var_value = get_env_value(var_name);
		if (var_value)
		{
			ft_strcpy(&new_str[*j], var_value);
			*j += ft_strlen(var_value);
			free(var_value);
		}
		*i += ft_strlen(var_name);
		free(var_name);
	}
	else
		new_str[(*j)++] = old_str[*i];
}

char	*get_var_name(const char *str)
{
	int		len;
	char	*name;

	len = 0;
	if (!ft_isalpha(str[len]) && str[len] != '_')
		return (NULL);
	len++;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, len + 1);
	return (name);
}

int	get_var_expanded_len(const char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	int		len;

	len = 0;
	var_name = get_var_name(&str[*i + 1]);
	if (var_name)
	{
		var_value = get_env_value(var_name);
		if (var_value)
		{
			len = ft_strlen(var_value);
			free(var_value);
		}
		*i += ft_strlen(var_name);
		free(var_name);
	}
	return (len);
}

int	get_len_of_dollar_expansion(const char *str, int *i)
{
	char	*status_str;
	int		len;

	len = 0;
	if (str[*i + 1] == '?')
	{
		status_str = ft_itoa(get_exit_status());
		len = ft_strlen(status_str);
		free(status_str);
		(*i)++;
	}
	else
	{
		len = get_var_expanded_len(str, i);
	}
	return (len);
}

int	get_expanded_len(const char *str)
{
	int		i;
	int		len;
	int		in_squote;

	i = 0;
	len = 0;
	in_squote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_squote = !in_squote;
		if (str[i] == '$' && !in_squote)
			len += get_len_of_dollar_expansion(str, &i);
		else
			len++;
		i++;
	}
	return (len);
}
