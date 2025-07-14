/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:23:11 by gabriel           #+#    #+#             */
/*   Updated: 2025/07/14 16:35:56 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*process_logical_op(t_parser *parser, t_ast_node *left)
{
	t_ast_node		*op_node;
	t_token_type	op_type;
	t_node_type		node_type;

	op_type = parser->current_token->type;
	next_token(parser);
	if (!parser->current_token)
		return (syntax_error(NULL), free_ast(left), NULL);
	if (op_type == TOKEN_OR)
		node_type = NODE_OR;
	else
		node_type = NODE_AND;
	op_node = create_ast_node(node_type);
	op_node->u_as.operator.left = left;
	op_node->u_as.operator.right = parse_pipe(parser);
	if (!op_node->u_as.operator.right)
		return (free_ast(op_node), NULL);
	return (op_node);
}

t_ast_node	*parse_logical_op(t_parser *parser)
{
	t_ast_node	*left;

	left = parse_pipe(parser);
	if (!left)
		return (NULL);
	while (parser->current_token && (parser->current_token->type == TOKEN_AND
			|| parser->current_token->type == TOKEN_OR))
	{
		left = process_logical_op(parser, left);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast_node	*parse_pipe(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;

	left = parse_primary(parser);
	if (!left)
		return (NULL);
	while (parser->current_token && parser->current_token->type == TOKEN_PIPE)
	{
		next_token(parser);
		if (!parser->current_token)
			return (syntax_error(NULL), free_ast(left), NULL);
		if (parser->current_token->type != TOKEN_WORD
			&& parser->current_token->type != TOKEN_LPAREN)
			return (syntax_error(parser->current_token->value),
				free_ast(left), NULL);
		pipe_node = create_ast_node(NODE_PIPE);
		pipe_node->u_as.operator.left = left;
		pipe_node->u_as.operator.right = parse_primary(parser);
		if (!pipe_node->u_as.operator.right)
			return (free_ast(pipe_node), NULL);
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
	if (!parser->current_token || parser->current_token->type != TOKEN_WORD)
	{
		if (parser->current_token)
			return (syntax_error(parser->current_token->value));
		else
			return (syntax_error("newline"));
	}
	redir = create_redir(type, parser->current_token->value);
	add_redir_to_node(node, redir);
	return (0);
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_parser	parser;

	if (!tokens)
		return (NULL);
	if (tokens->type != TOKEN_WORD && tokens->type != TOKEN_LPAREN)
		return (syntax_error(tokens->value), NULL);
	parser.current_token = tokens;
	return (parse_logical_op(&parser));
}
