/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:19:28 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/26 18:47:38 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_file(t_redir *redir)
{
	int	file_fd;

	file_fd = -1;
	if (redir->type == TOKEN_REDIR_IN)
		file_fd = open(redir->filename, O_RDONLY);
	else if (redir->type == TOKEN_REDIR_OUT)
		file_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_REDIR_APPEND)
		file_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
		perror(redir->filename);
	return (file_fd);
}

static int	handle_single_redir(t_redir *redir)
{
	int	file_fd;
	int	status;

	status = 0;
	file_fd = open_redir_file(redir);
	if (file_fd == -1)
		return (-1);
	if (redir->type == TOKEN_REDIR_IN)
	{
		if (dup2(file_fd, STDIN_FILENO) == -1)
			status = -1;
	}
	else
	{
		if (dup2(file_fd, STDOUT_FILENO) == -1)
			status = -1;
	}
	if (status == -1)
		perror("dup2");
	close(file_fd);
	return (status);
}

int	apply_redirections(t_command *cmd)
{
	t_redir	*current_redir;

	current_redir = cmd->redirections;
	while (current_redir)
	{
		if (handle_single_redir(current_redir) == -1)
			return (-1);
		current_redir = current_redir->next;
	}
	return (0);
}
