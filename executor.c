/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:57:02 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/29 19:16:17 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_parent_builtin(t_command *cmd)
{
	char	*name;

	if (!cmd || cmd->next != NULL || !cmd->args || !cmd->args[0])
		return (0);
	name = cmd->args[0];
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

static void	execute_pipeline(t_command *cmd, char **envp)
{
	int		pipe_fds[2];
	int		prev_read_end;
	pid_t	pid;

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
		parent_pipe_handler(pipe_fds, &prev_read_end, cmd);
		cmd = cmd->next;
	}
	waitpid(pid, NULL, 0);
	while (wait(NULL) > 0)
		;
}

void	executor(t_command *cmd, char **envp)
{
	if (!cmd)
		return ;
	if (is_parent_builtin(cmd))
	{
		dispatch_builtin(cmd, envp);
	}
	else
	{
		execute_pipeline(cmd, envp);
	}
}
