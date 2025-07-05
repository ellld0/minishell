/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:48:23 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/04 16:00:13 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *list_head)
{
	t_token	*current;
	t_token	*next_node;

	current = list_head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->value);
		free(current);
		current = next_node;
	}
}
