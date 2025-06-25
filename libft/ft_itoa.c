/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:07:46 by sdavi-al          #+#    #+#             */
/*   Updated: 2024/10/31 12:49:47 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	num_length(int num)
{
	int	length;

	length = 0;
	if (num <= 0)
		length = 1;
	while (num != 0)
	{
		num /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	long	num;
	int		length;
	char	*str;

	num = (long)n;
	length = num_length(num);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	else if (num == 0)
		str[0] = '0';
	length--;
	while (num > 0)
	{
		str[length] = (num % 10) + '0';
		num /= 10;
		length--;
	}
	return (str);
}

// #include <stdio.h>

// int main() {
//     char *result;

//     result = ft_itoa(1234);
//     printf("Input: 1234, Output: %s\n", result);
//     free(result);

//     result = ft_itoa(-5678);
//     printf("Input: -5678, Output: %s\n", result);
//     free(result);

//     result = ft_itoa(0);
//     printf("Input: 0, Output: %s\n", result);
//     free(result);

//     result = ft_itoa(5);
//     printf("Input: 5, Output: %s\n", result);
//     free(result);

//     result = ft_itoa(-3);
//     printf("Input: -3, Output: %s\n", result);
//     free(result);

//     result = ft_itoa(2147483647);
//     printf("Input: 2147483647, Output: %s\n", result);
//     free(result);

//     result = ft_itoa(-2147483648);
//     printf("Input: -2147483648, Output: %s\n", result);
//     free(result);

//     return 0;
// }
