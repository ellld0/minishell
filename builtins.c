/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:48:42 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/29 19:15:45 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}

void	do_echo(char **args)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline_flag)
		printf("\n");
}

static char	*ft_getenv(const char *name, char **envp)
{
	int		i;
	int		name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0)
		{
			if (envp[i][name_len] == '=')
				return (envp[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

void	do_cd(char **args, char **envp)
{
	char	*path;

	path = args[1];
	if (path == NULL)
	{
		path = ft_getenv("HOME", envp);
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return ;
		}
	}
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
	}
}

void	do_exit(char **args)
{
	int	status;

	printf("exit\n");
	if (args[1] && args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	if (args[1])
	{
		status = ft_atoi(args[1]);
		exit(status);
	}
	exit(0);
}
