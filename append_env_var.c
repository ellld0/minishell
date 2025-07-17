/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:06:25 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/17 19:06:30 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	construct_and_update_var(t_shell *shell, char *name, char *value)
{
	char	*final_env_str;
	char	*temp;

	temp = ft_strjoin(name, "=");
	final_env_str = ft_strjoin(temp, value);
	add_or_update_env_var(shell, final_env_str);
	free(temp);
	free(final_env_str);
}

void	append_to_env_var(t_shell *shell, char *append_expr)
{
	char	*var_name;
	char	*value_to_append;
	char	*old_value;
	char	*new_value;
	char	*plus_equals_ptr;

	plus_equals_ptr = ft_strnstr(append_expr, "+=", ft_strlen(append_expr));
	if (!plus_equals_ptr)
		return ;
	var_name = ft_substr(append_expr, 0, plus_equals_ptr - append_expr);
	value_to_append = ft_strdup(plus_equals_ptr + 2);
	old_value = get_env_value(shell->env, var_name);
	if (old_value)
		new_value = ft_strjoin(old_value, value_to_append);
	else
		new_value = ft_strdup(value_to_append);
	construct_and_update_var(shell, var_name, new_value);
	free(var_name);
	free(value_to_append);
	free(new_value);
}
