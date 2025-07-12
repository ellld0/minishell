/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:22:42 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/09 15:25:32 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_char_list(t_list *char_list)
{
	char	*str;
	int		len;
	int		i;
	t_list	*current;

	len = ft_lstsize(char_list);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	current = char_list;
	while (current)
	{
		str[i++] = *((char *)current->content);
		current = current->next;
	}
	str[i] = '\0';
	return (str);
}

static void	process_char_for_removal(char c, char *quote_state, t_list **list)
{
	char	*char_to_add;

	if (*quote_state == 0 && (c == '\'' || c == '\"'))
	{
		*quote_state = c;
		return ;
	}
	if (*quote_state != 0 && c == *quote_state)
	{
		*quote_state = 0;
		return ;
	}
	char_to_add = malloc(sizeof(char));
	if (!char_to_add)
		return ;
	*char_to_add = c;
	ft_lstadd_back(list, ft_lstnew(char_to_add));
}

char	*remove_quotes(char *str)
{
	t_list	*char_list;
	char	*final_str;
	int		i;
	char	quote_state;

	if (!str)
		return (NULL);
	char_list = NULL;
	quote_state = 0;
	i = 0;
	while (str[i])
	{
		process_char_for_removal(str[i], &quote_state, &char_list);
		i++;
	}
	final_str = join_char_list(char_list);
	ft_lstclear(&char_list, free);
	free(str);
	return (final_str);
}