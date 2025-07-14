/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:02:19 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/14 14:13:47 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(shell->env[i], 1);
		i++;
	}
}

static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;
	int	ret_status;

	ret_status = 0;
	if (argv[1] == NULL)
	{
		print_export_env(shell);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret_status = 1;
		}
		else if (ft_strchr(argv[i], '='))
			add_or_update_env_var(shell, argv[i]);
		i++;
	}
	return (ret_status);
}

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
