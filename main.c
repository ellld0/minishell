/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:33:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/10 13:12:45 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_token		*token_list;
	t_ast_node	*ast_root;
	int			last_status;

	last_status = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			token_list = main_lexer(line);
			print_token_list(token_list);
			ast_root = build_ast(token_list);
			print_ast(ast_root);
			if (ast_root)
				last_status = execute_ast(ast_root);
			free_token_list(token_list);
		}
		free(line);
	}
	return (last_status);
}
