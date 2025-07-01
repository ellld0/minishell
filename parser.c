/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:15 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 18:47:31 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words_in_segment(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			count++;
		if (token->type >= TOKEN_REDIR_IN && token->type <= TOKEN_HEREDOC)
			token = token->next;
		if (token)
			token = token->next;
	}
	return (count);
}

t_command	*process_segment(t_token **token_ptr)
{
	t_command	*cmd;

	cmd = init_command(*token_ptr);
	if (!cmd)
		return (NULL);
	populate_command(cmd, token_ptr);
	return (cmd);
}

t_command	*parser(t_token *tokens)
{
	t_command	*cmd_head;
	t_command	*new_cmd;
	t_token		*current_token;

	cmd_head = NULL;
	current_token = tokens;
	while (current_token)
	{
		new_cmd = process_segment(&current_token);
		cmd_add_back(&cmd_head, new_cmd);
		if (current_token && current_token->type == TOKEN_PIPE)
			current_token = current_token->next;
	}
	return (cmd_head);
}
