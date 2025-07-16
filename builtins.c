/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:12:48 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/16 18:42:24 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], 1);
		i++;
	}
	return (0);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_option)
		ft_putstr_fd("\n", 1);
	return (0);
}

static char	*get_cd_path(t_shell *shell, char **argv)
{
	char	*path;

	if (argv[1] == NULL)
	{
		path = get_env_value(shell->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
		return (path);
	}
	if (argv[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	return (argv[1]);
}

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*path;

	path = get_cd_path(shell, argv);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror(path);
		return (1);
	}
	return (0);
}
