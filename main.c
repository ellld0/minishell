/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:33:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/14 14:42:37 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(t_shell *shell, char *line)
{
	char		*expanded_line;
	t_token		*token_list;
	t_ast_node	*ast_root;

	if (line[0] == '\0')
		return ;
	add_history(line);
	expanded_line = expand_env_vars(shell, line);
	free(line);
	token_list = main_lexer(expanded_line);
	free(expanded_line);
	if (token_list)
	{
		ast_root = build_ast(token_list);
		if (!ast_root)
			shell->last_exit_status = 2;
		else
			shell->last_exit_status = execute_ast(shell, ast_root);
		free_ast(ast_root);
	}
	free_token_list(token_list);
}

static void	interactive_shell(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		process_line(shell, line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	setup_interactive_mode_signals();
	if (init_shell_env(&shell, envp) != 0)
	{
		ft_putendl_fd("minishell: environment initialization failed", 2);
		return (1);
	}
	interactive_shell(&shell);
	free_shell_env(&shell);
	return (shell.last_exit_status);
}
