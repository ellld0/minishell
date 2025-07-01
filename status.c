/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:48:25 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/07/01 10:51:11 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*get_exit_status_ptr(void)
{
	static int	g_exit_status = 0;

	return (&g_exit_status);
}

void	set_exit_status(int status)
{
	int	*status_ptr;

	status_ptr = get_exit_status_ptr();
	*status_ptr = status;
}

int	get_exit_status(void)
{
	return (*(get_exit_status_ptr()));
}
