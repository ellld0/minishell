/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:08:21 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 09:14:32 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_add_back(t_redir **list, t_redir *new_redir)
{
	t_redir	*current;

	if (!list || !new_redir)
		return ;
	if (*list == NULL)
	{
		*list = new_redir;
		return ;
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_redir;
}

void	handle_file_redirection(t_command *cmd, t_token *redir_token)
{
	t_redir	*new_redir;
	t_token	*filename_token;

	filename_token = redir_token->next;
	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = redir_token->type;
	new_redir->next = NULL;
	if (filename_token && filename_token->type == TOKEN_WORD)
		new_redir->filename = remove_quotes(filename_token->value);
	else
	{
		new_redir->filename = NULL;
	}
	redir_add_back(&(cmd->redirections), new_redir);
}
