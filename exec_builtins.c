/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:55:17 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 10:59:16 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	return (0);
}

int	dispatch_builtin(t_command *cmd)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = do_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = do_pwd();
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = do_cd(cmd->args);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		do_exit(cmd->args);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		do_env();
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		do_export(cmd->args);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		do_unset(cmd->args);
	return (0);
}

void	execute_builtin(t_command *cmd)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(cmd) == -1)
	{
		close(original_stdin);
		close(original_stdout);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		do_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		do_pwd();
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		do_cd(cmd->args);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		do_exit(cmd->args);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
