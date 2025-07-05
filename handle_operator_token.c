/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:14:04 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/05 11:14:32 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator_token(t_token **list, const char *line)
{
	if (line[1] == line[0])
	{
		if (line[0] == '<')
			return (add_token_back(list, create_token("<<", TOKEN_HEREDOC)), 2);
		if (line[0] == '>')
			return (add_token_back(list, create_token(">>", TOKEN_REDIR_APPEND))
				, 2);
		if (line[0] == '&')
			return (add_token_back(list, create_token("&&", TOKEN_AND)), 2);
		if (line[0] == '|')
			return (add_token_back(list, create_token("||", TOKEN_OR)), 2);
	}
	if (line[0] == '|')
		return (add_token_back(list, create_token("|", TOKEN_PIPE)), 1);
	if (line[0] == '<')
		return (add_token_back(list, create_token("<", TOKEN_REDIR_IN)), 1);
	if (line[0] == '>')
		return (add_token_back(list, create_token(">", TOKEN_REDIR_OUT)), 1);
	if (line[0] == '(')
		return (add_token_back(list, create_token("(", TOKEN_LPAREN)), 1);
	if (line[0] == ')')
		return (add_token_back(list, create_token(")", TOKEN_RPAREN)), 1);
	return (0);
}
