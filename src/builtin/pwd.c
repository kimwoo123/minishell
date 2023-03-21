/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:12 by chajung           #+#    #+#             */
/*   Updated: 2023/03/02 14:19:13 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_command(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		exit_with_str("getcwd error in pwd command", EXIT_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	path = NULL;
}
