/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:36:47 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/17 13:39:47 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_ast_nodes(t_shell *shell, t_ast_node *node)
{
	char	**argv;
	char	*expanded_arg;
	int		i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		argv = node->u_as.command.argv;
		if (!argv)
			return ;
		i = 0;
		while (argv[i])
		{
			expanded_arg = expand_env_vars(shell, argv[i]);
			free(argv[i]);
			argv[i] = expanded_arg;
			i++;
		}
	}
	else
	{
		expand_ast_nodes(shell, node->u_as.operator.left);
		expand_ast_nodes(shell, node->u_as.operator.right);
	}
}
