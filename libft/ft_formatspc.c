/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formatspc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:09:39 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/01/22 13:06:07 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formatspc(va_list args, const char format)
{
	int	print_len;

	print_len = 0;
	if (format == 'c')
		print_len += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_len += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_len += ft_printptr(va_arg(args, size_t));
	else if (format == 'd' || format == 'i')
		print_len += ft_printnbr((long)va_arg(args, int));
	else if (format == 'u')
		print_len += ft_printnbr_unsigned((long)va_arg(args, int));
	else if (format == 'x' || format == 'X')
		print_len += ft_print_hex((long)va_arg(args, unsigned int), format);
	else if (format == '%')
		print_len += ft_printpercent();
	else
		print_len += write(1, "%%", 1);
	return (print_len);
}
