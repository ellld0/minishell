/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:48:42 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 11:09:12 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	do_echo(char **args)
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
	return (0);
}

int	do_cd(char **args)
{
	char	*path;

	path = args[1];
	if (path == NULL)
	{
		path = get_env_value("HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		if (args[1] == NULL)
			free(path);
		return (1);
	}
	if (args[1] == NULL)
		free(path);
	return (0);
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

int	do_env(void)
{
	t_list	*current;

	current = *(get_env_list());
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
}
