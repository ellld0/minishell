/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/26 09:58:20 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process_exec(char *path, char **args, char **envp)
{
	execve(path, args, envp);
	perror("minishell");
	free(path);
	exit(127);
}

static void	execute_single_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	path = find_command_path(cmd->args[0], envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return ;
	}
	if (pid == 0)
		child_process_exec(path, cmd->args, envp);
	waitpid(pid, NULL, 0);
	free(path);
}

static int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (1);
	return (0);
}

static void	execute_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		do_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		do_pwd();
}

void	executor(t_command *cmd, char **envp)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (cmd->next != NULL)
	{
		printf("Pipes are not handled yet.\n");
		return ;
	}
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd);
	}
	else
	{
		execute_single_command(cmd, envp);
	}
}