/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:23:11 by gabriel           #+#    #+#             */
/*   Updated: 2025/07/09 12:26:27 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_logical_op(t_parser *parser)
{
	t_ast_node		*left;
	t_ast_node		*op_node;
	t_token_type	op_type;
	t_node_type		node_type;

	left = parse_pipe(parser);
	while (parser->current_token && (parser->current_token->type == TOKEN_AND
			|| parser->current_token->type == TOKEN_OR))
	{
		op_type = parser->current_token->type;
		next_token(parser);
		if (op_type == TOKEN_AND)
			node_type = NODE_AND;
		else
			node_type = NODE_OR;
		op_node = create_ast_node(node_type);
		op_node->u_as.operator.left = left;
		op_node->u_as.operator.right = parse_pipe(parser);
		left = op_node;
	}
	return (left);
}

t_ast_node	*parse_pipe(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;

	left = parse_simple_cmd(parser);
	while (parser->current_token && parser->current_token->type == TOKEN_PIPE)
	{
		next_token(parser);
		pipe_node = create_ast_node(NODE_PIPE);
		pipe_node->u_as.operator.left = left;
		pipe_node->u_as.operator.right = parse_simple_cmd(parser);
		left = pipe_node;
	}
	return (left);
}

int	handle_redirection(t_parser *parser, t_ast_node *node)
{
	t_token_type	type;
	t_redir			*redir;

	type = parser->current_token->type;
	next_token(parser);
	if (parser->current_token && parser->current_token->type == TOKEN_WORD)
	{
		redir = create_redir(type, parser->current_token->value);
		add_redir_to_node(node, redir);
	}
	else
	{
		write(2, "Syntax error near redirection\n", 30);
		return (1);
	}
	return (0);
}

void	populate_argv(t_ast_node *node, char **argv_list, int argc)
{
	int	i;

	i = 0;
	node->u_as.command.argv = malloc(sizeof(char *) * (argc + 1));
	if (!node->u_as.command.argv)
		return ;
	while (i < argc)
	{
		node->u_as.command.argv[i] = argv_list[i];
		i++;
	}
	node->u_as.command.argv[argc] = NULL;
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_parser	parser;

	if (!tokens)
		return (NULL);
	parser.current_token = tokens;
	return (parse_logical_op(&parser));
}
