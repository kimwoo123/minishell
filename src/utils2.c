/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:25:48 by chajung           #+#    #+#             */
/*   Updated: 2023/03/21 11:25:58 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == FAILURE)
		ft_perror("dup2 error", EXIT_FAILURE);
}

void	ft_unlink(const char *path)
{
	if (unlink(path) == FAILURE)
		ft_perror("unlink error", EXIT_FAILURE);
}

void	ft_wait(int *wstatus)
{
	if (wait(wstatus) == FAILURE)
		ft_perror("wait error", EXIT_FAILURE);
}
