/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:29:14 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 11:18:34 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_env_node(const char *name)
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
			if (env_var[name_len] == '=' || env_var[name_len] == '\0')
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}

void	set_env_var(const char *name, const char *value)
{
	t_list	*node;
	char	*new_env_var;
	char	*temp;

	node = find_env_node(name);
	temp = ft_strjoin(name, "=");
	new_env_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_env_var)
		return ;
	if (node)
	{
		free(node->content);
		node->content = new_env_var;
	}
	else
	{
		ft_lstadd_back(get_env_list(), ft_lstnew(new_env_var));
	}
}

void	print_export(void)
{
	t_list	*current;
	char	*var;
	char	*eq_pos;

	current = *(get_env_list());
	while (current)
	{
		var = (char *)current->content;
		eq_pos = ft_strchr(var, '=');
		printf("declare -x ");
		if (eq_pos)
		{
			write(STDOUT_FILENO, var, eq_pos - var + 1);
			printf("\"%s\"\n", eq_pos + 1);
		}
		else
		{
			printf("%s\n", var);
		}
		current = current->next;
	}
}

static int	process_export_arg(char *arg)
{
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos != NULL)
	{
		*eq_pos = '\0';
		if (!is_valid_identifier(arg))
		{
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			*eq_pos = '=';
			return (1);
		}
		set_env_var(arg, eq_pos + 1);
		*eq_pos = '=';
	}
	else
	{
		if (!is_valid_identifier(arg))
		{
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			return (1);
		}
	}
	return (0);
}

int	do_export(char **args)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (args[1] == NULL)
	{
		print_export();
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
