/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:15 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/23 12:08:01 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts the number of WORD tokens in a given segment of the token list,
** stopping at the next pipe (|) or at the end of the list.
**
** This is used to determine how many arguments (argv entries) we need
** to allocate for the current command before building its argument array.
**
** Redirection tokens (>, >>, <, <<) are skipped when counting.
*/
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

/*
** Adds a new command node (t_command) to the end of the command list.
**
** If the list is empty, the new command becomes the first node.
** Otherwise, the function traverses the existing list and appends
** the new command at the end.
*/
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

/*
** Initializes a new t_command structure for the given token segment.
**
** Allocates memory for the t_command and its argv array,
** using the number of WORD tokens counted in the segment.
**
** Initializes redirections and next pointers to NULL.
**
** Returns the newly created command, or NULL on allocation failure.
*/
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

/*
** Processes a segment of tokens representing a single command
** (from the current position up to the next pipe or end of list).
**
** For each token:
** - If it's a redirection (>, >>, <, <<), handle_redirection() is called
**   to record the redirection inside the command struct.
** - If it's a WORD token, its value (with quotes removed) is added
**   to the argv array of the command.
**
** Returns the newly created and filled command.
*/
static t_command	*process_segment(t_token **token_ptr)
{
	t_command	*cmd;
	int			i;

	cmd = init_command(*token_ptr);
	if (!cmd)
		return (NULL);
	i = 0;
	while (*token_ptr && (*token_ptr)->type != TOKEN_PIPE)
	{
		if ((*token_ptr)->type >= TOKEN_REDIR_IN)
		{
			handle_redirection(cmd, token_ptr);
		}
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

/*
** The main parser function.
**
** Converts a flat linked list of tokens (t_token) produced by the lexer
** into a structured linked list of commands (t_command).
**
** Main responsibilities:
** Loop through the full token list, splitting it into segments.
** Each segment represents one command, ending at a pipe (|) or end of line.
**  For each segment, process_segment() is called to:
**    Count the number of arguments.
**    Store command arguments (argv) after removing quotes.
**    Handle input/output redirections.
** Commands are linked together in order, forming a complete pipeline chain.
**
** If a pipe token is found, the parser moves past it and continues
** processing the next command segment.
**
** Returns:
** - The head of the linked list of commands (t_command*), ready for execution.
**
** After this stage:
** - The execution phase can use this list to set up processes, pipes,
**   redirections, and run the commands.
*/

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
