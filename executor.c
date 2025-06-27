/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/27 11:14:17 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process_exec(t_command *cmd, char *path, char **envp)
{
	if (apply_redirections(cmd) == -1)
	{
		free(path);
		exit(1);
	}
	execve(path, cmd->args, envp);
	perror("minishell");
	free(path);
	exit(127);
}

static void	execute_single_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		return ;
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
		child_process_exec(cmd, path, envp);
	waitpid(pid, NULL, 0);
	free(path);
}

void	run_command_in_child(t_command *cmd, char **envp)
{
	char	*path;

	if (apply_redirections(cmd) == -1)
		exit(1);
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		exit(0);
	if (is_builtin(cmd->args[0]))
	{
		if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
			do_echo(cmd->args);
		else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
			do_pwd();
		exit(0);
	}
	path = find_command_path(cmd->args[0], envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror("minishell");
	free(path);
	exit(126);
}

void	executor(t_command *cmd, char **envp)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (cmd->next == NULL && (ft_strncmp(cmd->args[0], "cd", 3) == 0
			|| ft_strncmp(cmd->args[0], "exit", 5) == 0))
	{
		if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
			do_cd(cmd->args, envp);
		else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
			do_exit(cmd->args);
	}
	else if (cmd->next && cmd->next->next == NULL)
		execute_pipe(cmd, envp);
	else if (cmd->next == NULL)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			run_command_in_child(cmd, envp);
		waitpid(pid, NULL, 0);
	}
	else
		printf("More than one pipe is not handled yet.\n");
}
