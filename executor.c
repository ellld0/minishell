/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/25 18:12:52 by sdavi-al         ###   ########.fr       */
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

void	executor(t_command *cmd, char **envp)
{
	if (!cmd)
		return ;
	if (cmd->next != NULL)
	{
		printf("Pipes are not handled yet.\n");
		return ;
	}
	execute_single_command(cmd, envp);
}
