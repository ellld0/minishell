/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:54:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/29 19:17:19 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*search_in_dirs(char **dirs, char *cmd)
{
	char	*temp_path;
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		temp_path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**dirs;
	char	*path_var;
	char	*full_path;

	path_var = get_path_from_env(envp);
	if (!path_var)
		return (NULL);
	dirs = ft_split(path_var, ':');
	if (!dirs)
		return (NULL);
	full_path = search_in_dirs(dirs, cmd);
	free_split(dirs);
	return (full_path);
}
