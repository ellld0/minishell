/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:36:12 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/10 14:33:07 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* executor.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/07/09 16:00:00 by sdavi-al          #+#    #+#             */
/* Updated: 2025/07/09 16:00:00 by sdavi-al         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command_node(t_ast_node *node);
static int	execute_pipe_node(t_ast_node *node);

int	execute_ast(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (execute_command_node(node));
	if (node->type == NODE_PIPE)
		return (execute_pipe_node(node));
	if (node->type == NODE_AND)
	{
		if (execute_ast(node->u_as.operator.left) == 0)
			return (execute_ast(node->u_as.operator.right));
	}
	if (node->type == NODE_OR)
	{
		if (execute_ast(node->u_as.operator.left) != 0)
			return (execute_ast(node->u_as.operator.right));
	}
	return (1);
}

static int	execute_command_node(t_ast_node *node)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (!node->u_as.command.argv || !node->u_as.command.argv[0])
		return (0);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (apply_redirections(&node->u_as.command) != 0)
			exit(1);
		cmd_path = find_command_path(node->u_as.command.argv[0]);
		if (!cmd_path)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(node->u_as.command.argv[0], 2);
			exit(127);
		}
		execve(cmd_path, node->u_as.command.argv, NULL); // Note: env needs to be passed
		perror("execve");
		free(cmd_path);
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	execute_pipe_node(t_ast_node *node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	left_pid = fork();
	if (left_pid == -1)
		return (perror("fork"), 1);
	if (left_pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(execute_ast(node->u_as.operator.left));
	}
	right_pid = fork();
	if (right_pid == -1)
		return (perror("fork"), 1);
	if (right_pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_ast(node->u_as.operator.right));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	return (WEXITSTATUS(status));
}
