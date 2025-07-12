/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:34:48 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/12 17:47:47 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match(const char *pattern, const char *s)
{
	if (*pattern == '\0')
		return (*s == '\0');
	if (*pattern == '*')
	{
		if (*(pattern + 1) != '\0' && *s == '\0')
			return (0);
		if (match(pattern + 1, s))
			return (1);
		if (*s != '\0' && match(pattern, s + 1))
			return (1);
	}
	if (*pattern == *s)
		return (match(pattern + 1, s + 1));
	return (0);
}
