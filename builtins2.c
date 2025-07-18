/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:02:19 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/18 14:11:19 by sdavi-al         ###   ########.fr       */
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
	int	status;

	ft_putendl_fd("exit", 2);
	if (argv[1] == NULL)
		exit(shell->last_exit_status);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (argv[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	status = ft_atoi(argv[1]);
	exit((unsigned char)status);
}
