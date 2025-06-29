/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/29 19:16:10 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_io(t_command *cmd, int *pipe_fds, int prev_read_end)
{
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
}

void	execute_and_exit(t_command *cmd, char **envp)
{
	char	*path;

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

void	run_command_in_child(t_command *cmd, int *pipe_fds,
		int prev_read_end, char **envp)
{
	setup_child_io(cmd, pipe_fds, prev_read_end);
	execute_and_exit(cmd, envp);
}

void	parent_pipe_handler(int *pipe_fds, int *prev_read_end,
		t_command *cmd)
{
	if (*prev_read_end != STDIN_FILENO)
		close(*prev_read_end);
	if (cmd->next)
	{
		*prev_read_end = pipe_fds[0];
		close(pipe_fds[1]);
	}
}

void	wait_for_children(int last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
}
