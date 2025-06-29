/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/29 18:13:13 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch_builtin(t_command *cmd, char **envp)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		do_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		do_pwd();
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		do_cd(cmd->args, envp);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		do_exit(cmd->args);
	return (0);
}

static void	run_command_in_child(t_command *cmd, int *pipe_fds,
		int prev_read_end, char **envp)
{
	char	*path;

	if (prev_read_end != STDIN_FILENO)
	{
		dup2(prev_read_end, STDIN_FILENO);
		close(prev_read_end);
	}
	if (cmd->next)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	if (apply_redirections(cmd) == -1)
		exit(1);
	if (!cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(dispatch_builtin(cmd, envp));
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

static void	wait_for_children(int last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
}

void	executor(t_command *cmd, char **envp)
{
	int		pipe_fds[2];
	int		prev_read_end;
	pid_t	pid;

	if (!cmd)
		return ;
	if (cmd->next == NULL && is_builtin(cmd->args[0])
		&& (ft_strncmp(cmd->args[0], "cd", 3) == 0
			|| ft_strncmp(cmd->args[0], "exit", 5) == 0))
	{
		dispatch_builtin(cmd, envp);
		return ;
	}
	prev_read_end = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipe_fds) == -1)
				return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			run_command_in_child(cmd, pipe_fds, prev_read_end, envp);
		if (prev_read_end != STDIN_FILENO)
			close(prev_read_end);
		if (cmd->next)
		{
			prev_read_end = pipe_fds[0];
			close(pipe_fds[1]);
		}
		cmd = cmd->next;
	}
	wait_for_children(pid);
}
