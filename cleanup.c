/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:48:23 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/17 12:06:05 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *list_head)
{
	t_token	*current;
	t_token	*next_node;

	current = list_head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->value);
		free(current);
		current = next_node;
	}
}

static void	free_redir_list(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next_node;

	current = redir;
	while (current)
	{
		next_node = current->next;
		free(current->filename);
		free(current);
		current = next_node;
	}
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		free_argv(node->u_as.command.argv);
		if (node->u_as.command.redirections)
			free_redir_list(node->u_as.command.redirections);
	}
	else
	{
		free_ast(node->u_as.operator.left);
		free_ast(node->u_as.operator.right);
	}
	free(node);
}

void	cleanup_heredocs(int heredoc_count)
{
	int		i;
	char	*heredoc_index;
	char	*filename;

	i = 0;
	while (i < heredoc_count)
	{
		heredoc_index = ft_itoa(i);
		filename = ft_strjoin("/tmp/minishell_heredoc_", heredoc_index);
		unlink(filename);
		free(heredoc_index);
		free(filename);
		i++;
	}
}
