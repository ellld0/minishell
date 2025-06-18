/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:01:20 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/18 15:03:19 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *list)
{
	t_token	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->value);
		free(list);
		list = next_node;
	}
}
