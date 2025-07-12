/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:33:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/12 15:40:58 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interactive_shell(t_shell *shell)
{
	char		*line;
	t_token		*token_list;
	t_ast_node	*ast_root;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			token_list = main_lexer(line);
			ast_root = build_ast(token_list);
			if (ast_root)
				shell->last_exit_status = execute_ast(shell, ast_root);
			free_token_list(token_list);
			free_ast(ast_root);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	if (init_shell_env(&shell, envp) != 0)
	{
		ft_putendl_fd("minishell: environment initialization failed", 2);
		return (1);
	}
	interactive_shell(&shell);
	free_shell_env(&shell);
	return (shell.last_exit_status);
}
