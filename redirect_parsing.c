/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:08:21 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:01 by sdavi-al         ###   ########.fr       */
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

void	handle_redirection(t_command *cmd, t_token **token_ptr)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = (*token_ptr)->type;
	new_redir->next = NULL;
	*token_ptr = (*token_ptr)->next;
	if (*token_ptr && (*token_ptr)->type == TOKEN_WORD)
		new_redir->filename = remove_quotes((*token_ptr)->value);
	else
	{
		new_redir->filename = NULL;
	}
	redir_add_back(&(cmd->redirections), new_redir);
}