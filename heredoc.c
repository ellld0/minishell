/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:03:14 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 12:40:21 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc_file(int heredoc_index)
{
	char	*index_str;
	char	*filename;

	index_str = ft_itoa(heredoc_index);
	filename = ft_strjoin("/tmp/minishell_heredoc_", index_str);
	free(index_str);
	return (filename);
}

static void	read_heredoc_to_fd(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	process_single_heredoc(t_redir *redir, int *heredoc_count)
{
	char	*temp_filename;
	char	*delimiter;
	int		fd;

	delimiter = remove_quotes(redir->filename);
	temp_filename = create_heredoc_file(*heredoc_count);
	fd = open(temp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	read_heredoc_to_fd(fd, delimiter);
	close(fd);
	free(delimiter);
	free(redir->filename);
	redir->filename = temp_filename;
	redir->type = TOKEN_REDIR_IN;
	(*heredoc_count)++;
}

void	process_heredocs(t_ast_node *node, int *heredoc_count)
{
	t_redir	*redir;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		redir = node->u_as.command.redirections;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
				process_single_heredoc(redir, heredoc_count);
			redir = redir->next;
		}
	}
	else
	{
		process_heredocs(node->u_as.operator.left, heredoc_count);
		process_heredocs(node->u_as.operator.right, heredoc_count);
	}
}
