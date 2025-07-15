/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:59:45 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/15 13:54:50 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**convert_list_to_argv(t_list *arg_list)
{
	char	**argv;
	int		argc;
	int		i;
	t_list	*current;

	argc = ft_lstsize(arg_list);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	current = arg_list;
	while (i < argc)
	{
		argv[i] = (char *)current->content;
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static void	*cleanup_cmd_on_error(t_ast_node *node, t_list *arg_list)
{
	if (arg_list)
		ft_lstclear(&arg_list, free);
	if (node)
		free_ast(node);
	return (NULL);
}

static int	build_cmd_content(t_parser *parser, t_ast_node *node,
		t_list **arg_list)
{
	while (parser->current_token
		&& parser->current_token->type != TOKEN_PIPE
		&& parser->current_token->type != TOKEN_AND
		&& parser->current_token->type != TOKEN_OR
		&& parser->current_token->type != TOKEN_RPAREN)
	{
		if (parser->current_token->type >= TOKEN_REDIR_IN)
		{
			if (handle_redirection(parser, node) != 0)
				return (1);
		}
		else if (parser->current_token->type == TOKEN_WORD)
		{
			ft_lstadd_back(arg_list,
				ft_lstnew(ft_strdup(parser->current_token->value)));
		}
		next_token(parser);
	}
	return (0);
}

t_ast_node	*parse_simple_cmd(t_parser *parser)
{
	t_list		*arg_list;
	t_ast_node	*node;

	arg_list = NULL;
	if (!parser->current_token)
		return (NULL);
	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	if (build_cmd_content(parser, node, &arg_list) != 0)
		return (cleanup_cmd_on_error(node, arg_list));
	node->u_as.command.argv = convert_list_to_argv(arg_list);
	ft_lstclear(&arg_list, NULL);
	if (!node->u_as.command.argv && ft_lstsize(arg_list) > 0)
		return (cleanup_cmd_on_error(node, NULL));
	return (node);
}
