/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:20:47 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/12 17:47:43 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static void	add_matches_to_list(t_list **matches, char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			if (match(pattern, entry->d_name))
				ft_lstadd_back(matches, ft_lstnew(ft_strdup(entry->d_name)));
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

static void	expand_argument(t_list **new_argv, char *arg)
{
	t_list	*matches;
	t_list	*current;

	if (ft_strchr(arg, '*') == NULL)
	{
		ft_lstadd_back(new_argv, ft_lstnew(ft_strdup(arg)));
		return ;
	}
	matches = NULL;
	add_matches_to_list(&matches, arg);
	if (ft_lstsize(matches) == 0)
	{
		ft_lstadd_back(new_argv, ft_lstnew(ft_strdup(arg)));
	}
	else
	{
		ft_lstsort(matches, ft_strcmp);
		current = matches;
		while (current)
		{
			ft_lstadd_back(new_argv, ft_lstnew(current->content));
			current = current->next;
		}
	}
	ft_lstclear(&matches, NULL);
}

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

void	expand_wildcards(t_ast_node *node)
{
	t_list	*new_argv_list;
	char	**original_argv;
	int		i;

	if (node->type != NODE_COMMAND)
		return ;
	new_argv_list = NULL;
	original_argv = node->u_as.command.argv;
	i = 0;
	while (original_argv[i])
	{
		expand_argument(&new_argv_list, original_argv[i]);
		i++;
	}
	free_argv(original_argv);
	node->u_as.command.argv = convert_list_to_argv(new_argv_list);
	ft_lstclear(&new_argv_list, NULL);
}
