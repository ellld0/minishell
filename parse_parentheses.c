/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:31:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 12:43:38 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*parse_parenthesized_group(t_parser *parser)
{
	t_ast_node		*node;
	t_token_type	next_type;

	next_token(parser);
	if (!parser->current_token)
		return (syntax_error("`(' not closed"), NULL);
	next_type = parser->current_token->type;
	if (next_type == TOKEN_AND || next_type == TOKEN_OR
		|| next_type == TOKEN_PIPE || next_type == TOKEN_RPAREN)
	{
		return (syntax_error(parser->current_token->value), NULL);
	}
	node = parse_logical_op(parser);
	if (!node)
		return (NULL);
	if (!parser->current_token
		|| parser->current_token->type != TOKEN_RPAREN)
	{
		syntax_error("`(' not closed");
		free_ast(node);
		return (NULL);
	}
	next_token(parser);
	return (node);
}

t_ast_node	*parse_primary(t_parser *parser)
{
	if (parser->current_token && parser->current_token->type == TOKEN_LPAREN)
		return (parse_parenthesized_group(parser));
	return (parse_simple_cmd(parser));
}
