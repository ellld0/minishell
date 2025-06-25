/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:19:24 by sdavi-al          #+#    #+#             */
/*   Updated: 2024/10/31 12:51:48 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*resultc;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	resultc = malloc(len + 1);
	if (!resultc)
		return (NULL);
	i = 0;
	while (i < len)
	{
		resultc[i] = f(i, s[i]);
		i++;
	}
	resultc[len] = '\0';
	return (resultc);
}
