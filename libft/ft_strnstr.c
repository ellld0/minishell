/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:40:04 by sdavi-al          #+#    #+#             */
/*   Updated: 2024/10/31 12:51:52 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	find_len;
	size_t	i;

	find_len = ft_strlen(to_find);
	if (find_len == 0)
		return ((char *)(str));
	if (len == 0)
		return (NULL);
	i = 0;
	while (str[i] && i + find_len <= len)
	{	
		if (ft_strncmp(&str[i], to_find, find_len) == 0)
			return ((char *)(&str[i]));
		i++;
	}
	return (NULL);
}
