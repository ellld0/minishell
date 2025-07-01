/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:15 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 06:19:45 by sdavi-al         ###   ########.fr       */
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

static void	cmd_add_back(t_command **list, t_command *new_cmd)
{
	t_command	*current;

	if (!list || !new_cmd)
		return ;
	if (*list == NULL)
	{
		*list = new_cmd;
		return ;
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_cmd;
}

static t_command	*init_command(t_token *token_segment)
{
	t_command	*cmd;
	int			word_count;

	word_count = count_words_in_segment(token_segment);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (word_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_command	*process_segment(t_token **token_ptr)
{
	t_command	*cmd;
	int			i;

	cmd = init_command(*token_ptr);
	if (!cmd)
		return (NULL);
	i = 0;
	while (*token_ptr && (*token_ptr)->type != TOKEN_PIPE)
	{
		if ((*token_ptr)->type == TOKEN_HEREDOC)
			handle_heredoc(cmd, token_ptr);
		else if ((*token_ptr)->type >= TOKEN_REDIR_IN)
			handle_file_redirection(cmd, token_ptr);
		else if ((*token_ptr)->type == TOKEN_WORD)
		{
			cmd->args[i++] = remove_quotes((*token_ptr)->value);
		}
		if (*token_ptr)
			*token_ptr = (*token_ptr)->next;
	}
	cmd->args[i] = NULL;
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
