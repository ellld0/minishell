/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:02:30 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 12:43:13 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_left_child(t_shell *shell, t_ast_node *node, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit(execute_ast(shell, node));
}

static void	execute_right_child(t_shell *shell, t_ast_node *node, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exit(execute_ast(shell, node));
}

static int	wait_for_pipeline(pid_t left_pid, pid_t right_pid)
{
	int	status;

	setup_execution_mode_signals();
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	setup_interactive_mode_signals();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit: 3", 2);
		else if (WTERMSIG(status) == SIGINT)
			ft_putendl_fd("", 2);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipe_node(t_shell *shell, t_ast_node *node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	left_pid = fork();
	if (left_pid == -1)
		return (perror("fork"), 1);
	if (left_pid == 0)
		execute_left_child(shell, node->u_as.operator.left, pipefd);
	right_pid = fork();
	if (right_pid == -1)
		return (perror("fork"), 1);
	if (right_pid == 0)
		execute_right_child(shell, node->u_as.operator.right, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_for_pipeline(left_pid, right_pid));
}
