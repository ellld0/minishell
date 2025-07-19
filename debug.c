/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:44:06 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 12:40:58 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_AND)
		return ("AND");
	if (type == TOKEN_OR)
		return ("OR");
	if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == TOKEN_LPAREN)
		return ("L_PAREN");
	if (type == TOKEN_RPAREN)
		return ("R_PAREN");
	return ("UNKNOWN");
}

void	print_token_list(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("Token %d: ", i++);
		printf("Type = %s, ", get_token_type_str(list->type));
		printf("Value = [%s]\n", list->value);
		list = list->next;
	}
}
