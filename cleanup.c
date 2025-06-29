/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:01:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/29 19:15:52 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *list)
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

void	free_command_table(t_command *cmd_head)
{
	t_command	*next_cmd;
	t_redir		*next_redir;
	int			i;

	while (cmd_head)
	{
		next_cmd = cmd_head->next;
		i = 0;
		while (cmd_head->args && cmd_head->args[i])
		{
			free(cmd_head->args[i]);
			i++;
		}
		if (cmd_head->args)
			free(cmd_head->args);
		while (cmd_head->redirections)
		{
			next_redir = cmd_head->redirections->next;
			if (cmd_head->redirections->filename)
				free(cmd_head->redirections->filename);
			free(cmd_head->redirections);
			cmd_head->redirections = next_redir;
		}
		free(cmd_head);
		cmd_head = next_cmd;
	}
}
