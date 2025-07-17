/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:48:44 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/17 19:06:18 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_count(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

static int	find_env_var(char **env, const char *var_name)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, name_len) == 0
			&& (env[i][name_len] == '=' || env[i][name_len] == '\0'))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	add_or_update_env_var(t_shell *shell, char *new_var)
{
	int		i;
	int		count;
	char	**new_env;
	char	*var_name;

	var_name = ft_substr(new_var, 0, ft_strchr(new_var, '=') - new_var);
	i = find_env_var(shell->env, var_name);
	free(var_name);
	if (i != -1)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strdup(new_var);
		return ;
	}
	count = get_env_count(shell->env);
	new_env = malloc(sizeof(char *) * (count + 2));
	i = -1;
	while (++i < count)
		new_env[i] = shell->env[i];
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	remove_env_var(t_shell *shell, const char *var_name)
{
	int		i;
	int		j;
	int		idx_to_remove;
	char	**new_env;

	idx_to_remove = find_env_var(shell->env, var_name);
	if (idx_to_remove == -1)
		return ;
	new_env = malloc(sizeof(char *) * get_env_count(shell->env));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (i != idx_to_remove)
			new_env[j++] = shell->env[i];
		i++;
	}
	new_env[j] = NULL;
	free(shell->env[idx_to_remove]);
	free(shell->env);
	shell->env = new_env;
}
