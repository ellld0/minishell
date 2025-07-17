/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:22:04 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/16 19:55:29 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir_out(t_redir *redir);
static int	handle_redir_in(char *filename);
static int	handle_heredoc(t_redir *redir);

int	apply_redirections(t_cmd_node *cmd)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_REDIR_APPEND)
		{
			if (handle_redir_out(redir) != 0)
				return (1);
		}
		else if (redir->type == TOKEN_REDIR_IN)
		{
			if (handle_redir_in(redir->filename) != 0)
				return (1);
		}
		else if (redir->type == TOKEN_HEREDOC)
		{
			if (handle_heredoc(redir) != 0)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

static int	handle_redir_out(t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->type == TOKEN_REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(redir->filename, flags, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static void	read_heredoc_input(int write_fd, char *delimiter)
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
		ft_putendl_fd(line, write_fd);
		free(line);
	}
}

static int	handle_heredoc(t_redir *redir)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	redir->filename = remove_quotes(redir->filename);
	read_heredoc_input(pipefd[1], redir->filename);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		return (1);
	}
	close(pipefd[0]);
	return (0);
}
