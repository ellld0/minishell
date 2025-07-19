/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:05:13 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 12:43:19 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(t_shell *shell)
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

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (0);
	return (1);
}

void	process_export_argument(t_shell *shell, char *arg, int *ret_status)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*ret_status = 1;
	}
	else if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		append_to_env_var(shell, arg);
	else if (ft_strchr(arg, '='))
		add_or_update_env_var(shell, arg);
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
		process_export_argument(shell, argv[i], &ret_status);
		i++;
	}
	return (ret_status);
}
