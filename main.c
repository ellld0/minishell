/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:33:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/18 14:46:41 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token_list(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("Token %d: ", i++);
		printf("Type = %d, ", list->type);
		printf("Value = [%s]\n", list->value);
		list = list->next;
	}
}

static void	free_token_list(t_token *list)
{
	t_token	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->value);
		free(list);
		list = next_node;
	}
}

int	main(void)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			printf("--- Lexer Output ---\n");
			tokens = main_lexer(line);
			print_token_list(tokens);
			free_token_list(tokens);
			printf("--------------------\n");
		}
		free(line);
	}
	return (0);
}
