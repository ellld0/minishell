/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:46:22 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 18:46:29 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_status_value(char *new_str, int *j)
{
	char	*status_str;

	status_str = ft_itoa(get_exit_status());
	ft_strcpy(&new_str[*j], status_str);
	*j += ft_strlen(status_str);
	free(status_str);
}

void	copy_dollar_expansion(char *new_str, int *j, const char *old_str,
			int *i)
{
	if (old_str[*i + 1] == '?')
	{
		copy_status_value(new_str, j);
		*i += 2;
	}
	else
	{
		copy_var_value(new_str, j, old_str, i);
	}
}

void	process_expansion_char(char *new, const char *old, t_exp_state *s)
{
	if (old[s->i] == '\'')
	{
		new[s->j++] = old[s->i++];
		s->in_squote = !(s->in_squote);
	}
	else if (old[s->i] == '$' && old[s->i + 1] == '?' && !(s->in_squote))
	{
		copy_status_value(new, &(s->j));
		s->i += 2;
	}
	else if (old[s->i] == '$' && !(s->in_squote))
	{
		copy_var_value(new, &(s->j), old, &(s->i));
	}
	else
	{
		new[s->j++] = old[s->i++];
	}
}

void	perform_expansion(char *new_str, const char *old_str)
{
	t_exp_state	state;

	state.i = 0;
	state.j = 0;
	state.in_squote = 0;
	while (old_str[state.i])
	{
		process_expansion_char(new_str, old_str, &state);
	}
	new_str[state.j] = '\0';
}

char	*expand_variables(char *str)
{
	char	*expanded_str;
	int		expanded_len;

	expanded_len = get_expanded_len(str);
	expanded_str = (char *)malloc(sizeof(char) * (expanded_len + 1));
	if (!expanded_str)
		return (NULL);
	perform_expansion(expanded_str, str);
	free(str);
	return (expanded_str);
}
