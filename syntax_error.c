/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:28:36 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/14 14:29:07 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd((char *)token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	return (1);
}