/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:43:54 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/01/19 10:07:32 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	length;

	length = ft_strlen(s);
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[length]);
	while (length >= 0)
	{
		if (s[length] == (unsigned char)c)
			return ((char *)&s[length]);
		length--;
	}
	return (NULL);
}
