/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:04:30 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/01/22 13:06:22 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_printchar(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_printstr(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (write (1, "(null)", 6));
	while (str[len])
		ft_printchar(str[len++]);
	return (len);
}

int	ft_printnbr(int n)
{
	int		len;
	char	*str;

	str = ft_itoa(n);
	len = ft_printstr(str);
	free(str);
	return (len);
}
