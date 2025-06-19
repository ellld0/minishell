/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:03:25 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/19 13:06:11 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token *list)
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

void	print_command_table(t_command *cmd_head)
{
	t_command	*cmd;
	t_redir		*redir;
	int			i;
	int			j;

	printf("--- Parser Output ---\n");
	cmd = cmd_head;
	i = 0;
	while (cmd)
	{
		printf("--- Command %d ---\n", i++);
		j = 0;
		printf("  Args: ");
		while (cmd->args && cmd->args[j])
		{
			printf("[%s] ", cmd->args[j]);
			j++;
		}
		printf("\n");
		redir = cmd->redirections;
		j = 0;
		while (redir)
		{
			printf("  Redir %d: Type=%d, Filename=[%s]\n", j++, redir->type,
				redir->filename);
			redir = redir->next;
		}
		cmd = cmd->next;
		if (cmd)
			printf("  PIPE to next command\n");
	}
	printf("---------------------\n");
}