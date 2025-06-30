/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:13:37 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/30 20:12:39 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env_var(const char *name)
{
	t_list	**env_list_ptr;
	t_list	*current;
	t_list	*prev;
	int		name_len;

	env_list_ptr = get_env_list();
	current = *env_list_ptr;
	prev = NULL;
	name_len = ft_strlen(name);
	while (current)
	{
		if (ft_strncmp((char *)current->content, name, name_len) == 0
			&& (((char *)current->content)[name_len] == '='
			|| ((char *)current->content)[name_len] == '\0'))
		{
			if (prev == NULL)
				*env_list_ptr = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, free);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	do_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
		}
		else
		{
			unset_env_var(args[i]);
		}
		i++;
	}
}
