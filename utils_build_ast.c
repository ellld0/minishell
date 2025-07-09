/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_build_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:31:03 by gabriel           #+#    #+#             */
/*   Updated: 2025/07/09 14:51:39 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_ast_node));
	new_node->type = type;
	return (new_node);
}

t_redir	*create_redir(t_token_type type, char *filename)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->filename = ft_strdup(filename);
	if (!new_redir->filename)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->next = NULL;
	return (new_redir);
}

void	add_redir_to_node(t_ast_node *node, t_redir *redir)
{
	t_redir	*current;

	if (!node || node->type != NODE_COMMAND)
		return ;
	if (!node->u_as.command.redirections)
	{
		node->u_as.command.redirections = redir;
	}
	else
	{
		current = node->u_as.command.redirections;
		while (current->next)
		{
			current = current->next;
		}
		current->next = redir;
	}
}

void	next_token(t_parser *parser)
{
	if (parser && parser->current_token)
	{
		parser->current_token = parser->current_token->next;
	}
}
