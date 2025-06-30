/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:48:42 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/30 15:26:43 by sdavi-al         ###   ########.fr       */
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

void	do_cd(char **args)
{
	char	*path;

	path = args[1];
	if (path == NULL)
	{
		path = get_env_value("HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return ;
		}
	}
	if (chdir(path) == -1)
		perror("minishell: cd");
	if (args[1] == NULL)
		free(path);
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

void	do_env(void)
{
	t_list	*current;

	current = *(get_env_list());
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}
