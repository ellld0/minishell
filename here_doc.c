/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:42:27 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 09:00:42 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_reader(const char *delimiter)
{
	char	*tmp_filename;
	int		fd;
	char	*line;

	tmp_filename = ft_strdup("/tmp/.minishell_heredoc");
	fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("heredoc file");
		free(tmp_filename);
		return (NULL);
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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (tmp_filename);
}

void	handle_heredoc(t_command *cmd, t_token *heredoc_token)
{
	t_redir	*new_redir;
	t_token	*delimiter_token;

	delimiter_token = heredoc_token->next;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = TOKEN_HEREDOC;
	new_redir->next = NULL;
	if (delimiter_token && delimiter_token->type == TOKEN_WORD)
	{
		// The reader now returns a filename string
		new_redir->filename = heredoc_reader(delimiter_token->value);
	}
	else
	{
		new_redir->filename = NULL; // Syntax error
	}
	redir_add_back(&(cmd->redirections), new_redir);
}

