/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:31:43 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/15 13:31:26 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_primary(t_parser *parser)
{
	t_ast_node	*node;

	if (parser->current_token && parser->current_token->type == TOKEN_LPAREN)
	{
		next_token(parser);
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
	return (parse_simple_cmd(parser));
}
