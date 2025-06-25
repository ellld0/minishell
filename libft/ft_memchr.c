/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:54:17 by sdavi-al          #+#    #+#             */
/*   Updated: 2024/10/31 12:50:23 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t n)
{
	const unsigned char	*cptr;
	unsigned char		ch;
	size_t				i;

	cptr = (const unsigned char *)ptr;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (cptr[i] == ch)
			return ((void *)&cptr[i]);
		i++;
	}
	return (NULL);
}
