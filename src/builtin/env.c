/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:15:03 by chajung           #+#    #+#             */
/*   Updated: 2023/03/08 14:15:04 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_path_in_envp(char **envp)
{
	size_t	index;

	index = 0;
	while (envp[index] && ft_strncmp(envp[index], "PATH=", ft_strlen("PATH=")))
		index++;
	if (!envp[index] || ft_strncmp(envp[index], "PATH=", ft_strlen("PATH=")))
		return (FAILURE);
	return (SUCCESS);
}

void	env_command(t_data *data)
{
	size_t	index;

	index = 0;
	if (data->copied_envp == NULL \
	|| find_path_in_envp(data->copied_envp) == FAILURE)
	{
		ft_putendl_fd("env: No such file or directory", STDERR_FILENO);
		return ;
	}
	while (data->copied_envp[index])
	{
		if (check_equal_sign(data->copied_envp[index]))
			ft_putendl_fd(data->copied_envp[index], STDOUT_FILENO);
		index++;
	}
}
