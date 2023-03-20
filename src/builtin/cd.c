/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:08:45 by chajung           #+#    #+#             */
/*   Updated: 2023/03/02 13:08:47 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_directory_to_home(char **commands, char **envp)
{
	char	*home_path;
	char	*path;

	home_path = find_home_path(envp);
	if (home_path == NULL)
		return (FAILURE);
	if (commands[1] == NULL \
		|| !ft_strncmp(commands[1], "~", ft_strlen(commands[1])) \
		|| !ft_strncmp(commands[1], "~/", ft_strlen(commands[1])))
		ft_chdir(home_path, commands[1]);
	else
	{
		path = ft_strjoin_wslash(home_path, &commands[1][2]);
		if (path == NULL)
			return (FAILURE);
		ft_chdir(path, commands[1]);
		free(path);
	}
	return (SUCCESS);
}

static int	change_directory_to_root(char **commands)
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

static int	change_directory(char **commands)
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

int	cd_command(t_data *data)
{
	char	*path;
	char	*temp;
	char	*pwd_path;

	if (backup_working_directory(data) == FAILURE)
		return (FAILURE);
	if (data->commands[1] == NULL \
	|| !ft_strncmp(data->commands[1], "~", ft_strlen("~")))
	{
		if (change_directory_to_home(data->commands, data->copied_envp) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strncmp(data->commands[1], "/", ft_strlen("/")))
	{
		if (change_directory_to_root(data->commands) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (change_directory(data->commands) == FAILURE)
			return (FAILURE);
	}
	if (change_working_directory(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
