/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:53:40 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/19 16:02:46 by gabriede         ###   ########.fr       */
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

static void	process_char_for_expansion(t_shell *shell, const char *line,
	t_expansion_state *state)
{
	char	temp[2];

	if (line[state->i] == '\'' || line[state->i] == '\"')
	{
		if (state->quote_char == 0)
			state->quote_char = line[state->i];
		else if (state->quote_char == line[state->i])
			state->quote_char = 0;
	}
	if (line[state->i] == '$' && state->quote_char != '\'')
	{
		state->i += handle_variable(&state->new_str, &line[state->i], shell);
	}
	else
	{
		temp[0] = line[state->i];
		temp[1] = '\0';
		append_str(&state->new_str, temp);
		state->i++;
	}
}

char	*expand_env_vars(t_shell *shell, const char *line)
{
	t_expansion_state	state;

	state.new_str = ft_strdup("");
	if (!state.new_str)
		return (NULL);
	state.i = 0;
	state.quote_char = 0;
	while (line[state.i])
	{
		process_char_for_expansion(shell, line, &state);
	}
	return (state.new_str);
}
