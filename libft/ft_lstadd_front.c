/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:39:32 by sdavi-al          #+#    #+#             */
/*   Updated: 2024/10/31 12:49:55 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)

{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*head;
// 	int		value1;
// 	int		value2;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list *current;

// 	value1 = 42;
// 	value2 = 24;

// 	node1 = ft_lstnew(&value1);
// 	node2 = ft_lstnew(&value2);

// 	ft_lstadd_front(&head, node1);

// 	ft_lstadd_front(&head, node2);

// 	current = head;
// 	while (current != NULL)
// 	{
// 		printf("Node content: %d\n", *(int *)current->content);
// 		current = current->next;
// 	}
// 	return (0);
// }
