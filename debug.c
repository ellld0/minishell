/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:03:25 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/06/18 18:09:55 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("Token %d: ", i++);
		printf("Type = %d, ", list->type);
		printf("Value = [%s]\n", list->value);
		list = list->next;
	}
}
