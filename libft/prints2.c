/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:08:31 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/01/22 13:06:31 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printptr(size_t ptr)
{
	int		len;
	char	buffer[17];
	int		i;

	len = 0;
	if (!ptr)
		return (ft_printstr("(nil)"));
	len += ft_printstr("0x");
	i = 16;
	buffer[i] = '\0';
	while (ptr > 0)
	{
		buffer[--i] = "0123456789abcdef"[ptr % 16];
		ptr /= 16;
	}
	len += ft_printstr(&buffer[i]);
	return (len);
}

int	ft_print_hex(unsigned int num, const char format)
{
	int	len;

	len = 0;
	if (num >= 16)
		len += ft_print_hex(num / 16, format);
	if (format == 'x')
		len += ft_printchar("0123456789abcdef"[num % 16]);
	else if (format == 'X')
		len += ft_printchar("0123456789ABCDEF"[num % 16]);
	return (len);
}

int	ft_printnbr_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += ft_printnbr_unsigned(n / 10);
	len += ft_printchar((n % 10) + '0');
	return (len);
}

int	ft_printpercent(void)
{
	return (ft_printchar('%'));
}
