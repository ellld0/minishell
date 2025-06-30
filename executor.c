/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:57:02 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/30 15:49:24 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **env_arr)
{
	int	i;

	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		free(env_arr[i]);
		i++;
	}
	free(env_arr);
}

static int	is_parent_builtin(t_command *cmd)
{
	char	*name;

	if (!cmd || cmd->next != NULL || !cmd->args || !cmd->args[0])
		return (0);
	name = cmd->args[0];
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	return (0);
}

static void	execute_pipeline(t_command *cmd)
{
	int		pipe_fds[2];
	int		prev_read_end;
	pid_t	pid;

	prev_read_end = STDIN_FILENO;
	pid = -1;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipe_fds) == -1)
				return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			run_command_in_child(cmd, pipe_fds, prev_read_end);
		parent_pipe_handler(pipe_fds, &prev_read_end, cmd);
		cmd = cmd->next;
	}
	if (pid != -1)
		wait_for_children(pid);
}

void	executor(t_command *cmd)
{
	if (!cmd)
		return ;
	if (is_parent_builtin(cmd))
		dispatch_builtin(cmd);
	else
	{
		execute_pipeline(cmd);
	}
}
