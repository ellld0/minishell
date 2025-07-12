/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:35:46 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/12 17:36:39 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_content(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	ft_lstsort(t_list *lst, int (*cmp)())
{
	int		swapped;
	t_list	*current;

	if (!lst)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = lst;
		while (current && current->next)
		{
			if (cmp(current->content, current->next->content) > 0)
			{
				swap_content(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}
