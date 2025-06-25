/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:57:47 by sdavi-al          #+#    #+#             */
/*   Updated: 2024/10/31 12:50:56 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char	*cptr;
	unsigned char	value;

	cptr = (unsigned char *)ptr;
	value = (unsigned char)c;
	while (n--)
		*cptr++ = value;
	return (ptr);
}
