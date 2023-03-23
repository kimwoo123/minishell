/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:13:44 by chajung           #+#    #+#             */
/*   Updated: 2023/03/21 11:13:54 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	set_status(int stat)
{
	extern int	g_status;

	g_status = stat << 8;
}

void	exit_with_str(const char *str, int exit_code)
{
	ft_putendl_fd((char *)str, STDERR_FILENO);
	exit(exit_code);
}
