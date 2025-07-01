/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:50:39 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 17:44:08 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(const char *str)
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

static int	get_var_expanded_len(const char *str, int *i)
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

static int	get_len_of_dollar_expansion(const char *str, int *i)
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

static int	get_expanded_len(const char *str)
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

static void	copy_status_value(char *new_str, int *j)
{
	char	*status_str;

	status_str = ft_itoa(get_exit_status());
	ft_strcpy(&new_str[*j], status_str);
	*j += ft_strlen(status_str);
	free(status_str);
}

static void	copy_var_value(char *new_str, int *j, const char *old_str, int *i)
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

static void	perform_expansion(char *new_str, const char *old_str)
{
	int	i;
	int	j;
	int	in_squote;

	i = 0;
	j = 0;
	in_squote = 0;
	while (old_str[i])
	{
		if (old_str[i] == '\'')
		{
			new_str[j++] = old_str[i];
			in_squote = !in_squote;
		}
		else if (old_str[i] == '$' && old_str[i + 1] == '?' && !in_squote)
		{
			copy_status_value(new_str, &j);
			i++;
		}
		else if (old_str[i] == '$' && !in_squote)
			copy_var_value(new_str, &j, old_str, &i);
		else
			new_str[j++] = old_str[i];
		i++;
	}
	new_str[j] = '\0';
}

char	*expand_variables(char *str)
{
	char	*expanded_str;
	int		expanded_len;

	expanded_len = get_expanded_len(str);
	expanded_str = (char *)malloc(sizeof(char) * (expanded_len + 1));
	if (!expanded_str)
		return (NULL);
	perform_expansion(expanded_str, str);
	free(str);
	return (expanded_str);
}
