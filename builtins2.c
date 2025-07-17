/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:02:19 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/17 19:05:02 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_shell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_env_var(shell, argv[i]);
		i++;
	}
	return (0);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	(void)argv;
	ft_putendl_fd("exit", 2);
	exit(shell->last_exit_status);
}
