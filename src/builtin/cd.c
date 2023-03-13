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

#include "../../inc/minishell.h"

static void	ft_chdir(const char *path, const char *cmd)
{
	char	*error_str;

	if (chdir(path) == FAILURE)
	{
		if (cmd == NULL)
			perror("bash: cd: "); //need to fix
		else
		{
			error_str = ft_strjoin("bash: cd: ", cmd);
			if (error_str == NULL)
				ft_perror("strjoin error in ft_chdir function", EXIT_FAILURE);
			perror(error_str);
		}
	}
}

static char	*find_home_path(char **envp)
{
	size_t	index;

	if (!envp)
		return (NULL);
	index = 0;
	while (envp[index] && ft_strncmp(envp[index], "HOME=", ft_strlen("HOME=")))
		index++;
	if (!envp[index] || ft_strncmp(envp[index], "HOME=", ft_strlen("HOME=")))
			return (NULL);
	return (&(envp)[index][5]);
}

int	change_directory_to_home(char **commands, char **envp)
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
			ft_perror("strjoin_wslash error in cd command", EXIT_FAILURE);
		ft_chdir(path, commands[1]);
		free(path);
	}
	return (SUCCESS);
}

int	change_directory_to_root(char **commands, char **envp)
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

int	change_directory(char **commands, char **envp)
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

// need to add OLDPWD and exit code
int	cd_command(t_data *data)
{
	char	*path;
	char	*temp;
	char	*pwd_path;

	if (backup_working_directory(data) == FAILURE)
		return (FAILURE);
	if (data->commands[1] == NULL || !ft_strncmp(data->commands[1], "~", ft_strlen("~")))
	{
		change_directory_to_home(data->commands, data->envp);

	}
	else if (!ft_strncmp(data->commands[1], "/", ft_strlen("/")))
	{
		change_directory_to_root(data->commands, data->envp);

	}
	else
	{
		change_directory(data->commands, data->envp);

	}
	if (change_working_directory(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
