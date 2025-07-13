/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:53:40 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/13 14:16:01 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_str(char **dest, const char *src)
{
	char	*old_dest;
	char	*new_dest;

	if (!src)
		return ;
	old_dest = *dest;
	new_dest = ft_strjoin(old_dest, src);
	free(old_dest);
	*dest = new_dest;
}

static void	handle_exit_status(char **new_str, t_shell *shell)
{
	char	*status_str;

	status_str = ft_itoa(shell->last_exit_status);
	append_str(new_str, status_str);
	free(status_str);
}

static int	handle_variable(char **new_str, const char *line, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		name_len;

	if (line[1] == '?')
	{
		handle_exit_status(new_str, shell);
		return (2);
	}
	var_name = get_var_name(&line[1]);
	if (!var_name)
		return (1);
	name_len = ft_strlen(var_name);
	var_value = get_env_value(shell->env, var_name);
	if (var_value)
		append_str(new_str, var_value);
	free(var_name);
	return (name_len + 1);
}

char	*expand_env_vars(t_shell *shell, const char *line)
{
	char	*new_str;
	int		i;
	char	temp[2];

	new_str = ft_strdup("");
	i = 0;
	temp[1] = '\0';
	while (line[i])
	{
		if (line[i] == '$')
		{
			i += handle_variable(&new_str, &line[i], shell);
		}
		else
		{
			temp[0] = line[i];
			append_str(&new_str, temp);
			i++;
		}
	}
	return (new_str);
}
