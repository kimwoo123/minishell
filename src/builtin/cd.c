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

static int	change_dir_nothing(t_data *data)
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
	// free(path);
	return (SUCCESS);
}

static int	get_home_path(t_data *data, char **home_path)
{
	*home_path = find_home_path(data->envp);
	if (*home_path == NULL)
		return (FALSE);
	if (data->commands[1] == NULL)
	{
		*home_path = find_home_path(data->copied_envp);
		if (*home_path == NULL)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			set_status(EXIT_FAILURE);
			return (FAILURE);
		}
	}
	return (TRUE);
}

static int	change_dir_to_home(t_data *data)
{
	char	*home_path;
	char	*path;

	// result = get_home_path(data, &home_path);
	// if (result == FALSE)
	// 	return (FAILURE);
	// else if (result == FAILURE)
	// 	return (SUCCESS);

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

static int	change_dir_to_root(char **commands)
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

static int	change_dir(char **commands)
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

static int	change_directory(t_data *data)
{
	int	result;

	set_status(EXIT_SUCCESS);
	result = SUCCESS;
	if (data->commands[1] == NULL)
		result = change_dir_nothing(data);
	else if (!ft_strncmp(data->commands[1], "~", ft_strlen("~")))
		result = change_dir_to_home(data);
	else if (!ft_strncmp(data->commands[1], "/", ft_strlen("/")))
		result = change_dir_to_root(data->commands);
	else
		result = change_dir(data->commands);
	return (result);
}

void	cd_command(t_data *data)
{
	char	*path;

	if (backup_working_directory(data) == FAILURE)
		exit_with_str("backup error in cd command", EXIT_FAILURE);
	if (change_directory(data) == FAILURE)
		exit_with_str("cd error in cd command", EXIT_FAILURE);
	if (change_working_directory(data) == FAILURE)
		exit_with_str("backup error in cd command", EXIT_FAILURE);
}
