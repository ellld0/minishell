/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debugger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:38:44 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/09 14:30:05 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ast_recursive(t_ast_node *node, int level);

static void	print_indent(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		printf("  ");
		i++;
	}
}

static void	print_redirections(t_redir *r)
{
	printf(" [Redirs: ");
	while (r)
	{
		if (r->type == TOKEN_REDIR_OUT)
			printf(">");
		else if (r->type == TOKEN_REDIR_APPEND)
			printf(">>");
		else if (r->type == TOKEN_REDIR_IN)
			printf("<");
		else if (r->type == TOKEN_HEREDOC)
			printf("<<");
		printf(" %s, ", r->filename);
		r = r->next;
	}
	printf("\b\b] ");
}

static void	print_command_details(t_cmd_node *cmd_node)
{
	int	i;

	printf("CMD: ");
	i = 0;
	if (!cmd_node->argv)
	{
		printf("(null) ");
		return ;
	}
	while (cmd_node->argv[i])
	{
		printf("\"%s\" ", cmd_node->argv[i]);
		i++;
	}
	if (cmd_node->redirections)
		print_redirections(cmd_node->redirections);
}

static void	print_ast_recursive(t_ast_node *node, int level)
{
	if (!node)
		return ;
	print_indent(level);
	if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_AND)
		printf("AND (&&)\n");
	else if (node->type == NODE_OR)
		printf("OR (||)\n");
	else if (node->type == NODE_COMMAND)
	{
		print_command_details(&node->u_as.command);
		printf("\n");
	}
	if (node->type != NODE_COMMAND)
	{
		print_ast_recursive(node->u_as.operator.left, level + 1);
		print_ast_recursive(node->u_as.operator.right, level + 1);
	}
}

void	print_ast(t_ast_node *root)
{
	printf("--- Abstract Syntax Tree ---\n");
	if (!root)
		printf("  (NULL)\n");
	else
		print_ast_recursive(root, 0);
	printf("----------------------------\n");
}
