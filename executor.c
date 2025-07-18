/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:36:12 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 17:36:27 by gabriede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quotes_from_argv(char **argv)
{
	int		i;
	char	*unquoted_arg;

	i = 0;
	while (argv[i])
	{
		unquoted_arg = remove_quotes(argv[i]);
		free(argv[i]);
		argv[i] = unquoted_arg;
		i++;
	}
}

static void	child_process_execution(t_shell *shell, t_ast_node *node)
{
	char	*cmd_path;
	char	*cmd;

	if (node->u_as.command.argv)
		cmd = node->u_as.command.argv[0];
	else
		cmd = NULL;
	reset_child_signals();
	if (apply_redirections(&node->u_as.command) != 0)
		exit(1);
	if (!cmd)
		exit(0);
	if (is_builtin(cmd))
		exit(execute_builtin(shell, node->u_as.command.argv));
	cmd_path = find_command_path(cmd, shell);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(127);
	}
	execve(cmd_path, node->u_as.command.argv, shell->env);
	perror("execve");
	free(cmd_path);
	exit(126);
}

static int	parent_process_wait(pid_t pid)
{
	int	status;

	setup_execution_mode_signals();
	waitpid(pid, &status, 0);
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

int	execute_command_node(t_shell *shell, t_ast_node *node)
{
	pid_t	pid;
	char	*cmd;

	expand_wildcards(node);
	remove_quotes_from_argv(node->u_as.command.argv);
	if (node->u_as.command.argv)
		cmd = node->u_as.command.argv[0];
	else
		cmd = NULL;
	if (cmd && is_state_changing_builtin(cmd))
		return (execute_builtin(shell, node->u_as.command.argv));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		child_process_execution(shell, node);
	return (parent_process_wait(pid));
}

int	execute_ast(t_shell *shell, t_ast_node *node)
{
	int	status;

	if (!node)
		return (0);
	expand_ast_nodes(shell, node);
	if (node->type == NODE_COMMAND)
		return (execute_command_node(shell, node));
	if (node->type == NODE_PIPE)
		return (execute_pipe_node(shell, node));
	status = execute_ast(shell, node->u_as.operator.left);
	if (node->type == NODE_AND)
	{
		if (status == 0)
			return (execute_ast(shell, node->u_as.operator.right));
		return (status);
	}
	if (node->type == NODE_OR)
	{
		if (status != 0)
			return (execute_ast(shell, node->u_as.operator.right));
		return (status);
	}
	return (1);
}
