/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:07:42 by sdavi-al          #+#    #+#             */
/*   Updated: 2024/10/31 12:51:37 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (destsize <= dest_len)
		return (src_len + destsize);
	i = 0;
	while (i < src_len && (dest_len + i + 1) < destsize)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (dest_len + i < destsize)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
