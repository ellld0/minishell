/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:33:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/30 13:46:26 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;

	(void)argc;
	(void)argv;
	init_env(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0])
		{
			add_history(line);
			tokens = main_lexer(line);
			commands = parser(tokens);
			free_token_list(tokens);
			executor(commands);
			free_command_table(commands);
		}
		free(line);
	}
	free_env();
	return (0);
}
