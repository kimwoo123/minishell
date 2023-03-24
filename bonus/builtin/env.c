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

#include "minishell_bonus.h"

static void	print_no_such_file_or_directory(char *str)
{
	set_status(COMMAND_NOT_FOUND);
	ft_putstr_fd("env: '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': No such file or directory", STDERR_FILENO);
}

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
	else if (data->commands[1] != NULL)
	{
		print_no_such_file_or_directory(data->commands[1]);
		return ;
	}
	while (data->copied_envp[index])
	{
		if (check_equal_sign(data->copied_envp[index]))
			ft_putendl_fd(data->copied_envp[index], STDOUT_FILENO);
		index++;
	}
}
