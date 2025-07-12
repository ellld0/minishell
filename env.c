/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:36:15 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/12 15:37:38 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell_env(t_shell *shell, char **envp)
{
	int	count;
	int	i;

	count = 0;
	while (envp[count])
		count++;
	shell->env = malloc(sizeof(char *) * (count + 1));
	if (!shell->env)
		return (1);
	i = 0;
	while (i < count)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
		{
			while (i > 0)
				free(shell->env[--i]);
			free(shell->env);
			return (1);
		}
		i++;
	}
	shell->env[i] = NULL;
	return (0);
}

void	free_shell_env(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
	shell->env = NULL;
}
