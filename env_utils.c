/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:50:21 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 16:05:41 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, const char *var_name)
{
	int		i;
	int		name_len;

	i = 0;
	name_len = ft_strlen(var_name);
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(getpid()));
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, name_len) == 0)
		{
			if (env[i][name_len] == '=')
				return (env[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

char	*get_var_name(const char *str)
{
	int	len;

	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_' || str[len] == '$')
		len++;
	return (ft_substr(str, 0, len));
}
