/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:24:49 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/30 14:15:12 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**get_env_list(void)
{
	static t_list	*env_list = NULL;

	return (&env_list);
}

char	*get_env_value(const char *name)
{
	t_list	*current;
	char	*env_var;
	int		name_len;

	name_len = ft_strlen(name);
	current = *(get_env_list());
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, name, name_len) == 0)
		{
			if (env_var[name_len] == '=')
				return (ft_strdup(env_var + name_len + 1));
		}
		current = current->next;
	}
	return (NULL);
}

void	init_env(char **envp)
{
	t_list	**env_list_ptr;
	t_list	*new_node;
	char	*env_var_copy;
	int		i;

	env_list_ptr = get_env_list();
	i = 0;
	while (envp[i])
	{
		env_var_copy = ft_strdup(envp[i]);
		if (!env_var_copy)
			return ;
		new_node = ft_lstnew(env_var_copy);
		if (!new_node)
		{
			free(env_var_copy);
			return ;
		}
		ft_lstadd_back(env_list_ptr, new_node);
		i++;
	}
}

char	**env_list_to_array(void)
{
	t_list	*current;
	char	**env_array;
	int		size;
	int		i;

	current = *(get_env_list());
	size = ft_lstsize(current);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (current)
	{
		env_array[i] = ft_strdup((char *)current->content);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_env(void)
{
	t_list	**env_list_ptr;

	env_list_ptr = get_env_list();
	ft_lstclear(env_list_ptr, free);
}
