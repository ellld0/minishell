/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:19:12 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/14 14:09:53 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_shell *shell, char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(shell, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(shell, argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(shell, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(shell, argv));
	return (1);
}
