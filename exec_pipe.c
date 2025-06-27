/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:58:47 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/27 11:09:51 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child1_process(t_command *cmd, int *pipe_fds, char **envp)
{
	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	run_command_in_child(cmd, envp);
}

static void	child2_process(t_command *cmd, int *pipe_fds, char **envp)
{
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	run_command_in_child(cmd, envp);
}

static void	execute_pipe(t_command *cmd, char **envp)
{
	int		pipe_fds[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return ;
	}
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork"));
	if (pid1 == 0)
		child1_process(cmd, pipe_fds, envp);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork"));
	if (pid2 == 0)
		child2_process(cmd->next, pipe_fds, envp);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
