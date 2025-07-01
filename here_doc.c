/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:42:27 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 06:19:40 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_reader(const char *delimiter)
{
	int		pipe_fds[2];
	char	*line;

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

static void	handle_heredoc(t_command *cmd, t_token **token_ptr)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = (*token_ptr)->type;
	new_redir->filename = NULL;
	new_redir->next = NULL;
	*token_ptr = (*token_ptr)->next;
	if (*token_ptr && (*token_ptr)->type == TOKEN_WORD)
		new_redir->heredoc_fd = heredoc_reader((*token_ptr)->value);
	else
	{
		new_redir->heredoc_fd = -1;
	}
	redir_add_back(&(cmd->redirections), new_redir);
}

