/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:57:02 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/29 18:57:29 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		parent_pipe_handler(pipe_fds, &prev_read_end, cmd);
		cmd = cmd->next;
	}
	wait_for_children(pid);
}