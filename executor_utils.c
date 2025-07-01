/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 11:00:25 by sdavi-al         ###   ########.fr       */
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

void	execute_and_exit(t_command *cmd)
{
	char	*path;
	char	**env_arr;

	if (apply_redirections(cmd) == -1)
		exit(1);
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(dispatch_builtin(cmd));
	env_arr = env_list_to_array();
	path = find_command_path(cmd->args[0]);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		free_array(env_arr);
		exit(127);
	}
	execve(path, cmd->args, env_arr);
	perror("minishell");
	free(path);
	free_array(env_arr);
	exit(126);
}

void	run_command_in_child(t_command *cmd, int *pipe_fds,
		int prev_read_end)
{
	setup_child_io(cmd, pipe_fds, prev_read_end);
	execute_and_exit(cmd);
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
	int	exit_code;

	if (last_pid == -1)
		return ;
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		set_exit_status(exit_code);
	}
	while (wait(NULL) > 0)
		;
}
