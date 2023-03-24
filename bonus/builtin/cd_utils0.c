/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:28:44 by chajung           #+#    #+#             */
/*   Updated: 2023/03/13 09:28:45 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	change_dir_nothing(t_data *data)
{
	char	*path;

	path = find_home_path(data->copied_envp);
	if (path == NULL)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		set_status(EXIT_FAILURE);
		return (SUCCESS);
	}
	ft_chdir(path, path);
	return (SUCCESS);
}

int	change_dir_to_home(t_data *data)
{
	char	*home_path;
	char	*path;

	home_path = find_home_path(data->envp);
	if (!ft_strncmp(data->commands[1], "~", ft_strlen(data->commands[1])) \
	|| !ft_strncmp(data->commands[1], "~/", ft_strlen(data->commands[1])))
		ft_chdir(home_path, data->commands[1]);
	else
	{
		path = ft_strjoin_wslash(home_path, &data->commands[1][2]);
		if (path == NULL)
			return (FAILURE);
		ft_chdir(path, data->commands[1]);
		free(path);
	}
	return (SUCCESS);
}

int	change_dir_to_root(char **commands)
{
	char	*path;

	if (!ft_strncmp(commands[1], "/", ft_strlen(commands[1])))
		ft_chdir("/", commands[1]);
	else
	{
		path = ft_strjoin_wslash("/", &commands[1][1]);
		if (path == NULL)
			return (FAILURE);
		ft_chdir(path, commands[1]);
		free(path);
	}
	return (SUCCESS);
}

int	change_dir(char **commands)
{
	char	*current_path;
	char	*path;

	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
		return (FAILURE);
	path = ft_strjoin_wslash(current_path, commands[1]);
	if (path == NULL)
		return (FAILURE);
	free(current_path);
	ft_chdir(path, commands[1]);
	free(path);
	return (SUCCESS);
}
