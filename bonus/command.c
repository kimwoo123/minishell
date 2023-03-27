/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:31:44 by chajung           #+#    #+#             */
/*   Updated: 2023/03/27 17:37:25 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_envp_index(t_data *data)
{
	size_t	index;

	index = 0;
	while (data->copied_envp[index] \
	&& ft_strncmp(data->copied_envp[index], "PATH=", ft_strlen("PATH=")))
		index++;
	if (!data->envp[index] \
	|| ft_strncmp(data->envp[index], "PATH=", ft_strlen("PATH=")))
		return (FAILURE);
	return ((int)index);
}

static char	*check_access(t_data *data, char **split)
{
	size_t		index;
	char		*cmd;
	struct stat	finfo;

	stat(data->commands[0], &finfo);
	if (!S_ISDIR(finfo.st_mode))
	{
		if (!access(data->commands[0], X_OK))
			return (data->commands[0]);
	}
	index = -1;
	while (split[++index])
	{
		cmd = ft_strjoin_wslash(split[index], data->commands[0]);
		if (cmd == NULL)
			return (NULL);
		stat(cmd, &finfo);
		if (!S_ISDIR(finfo.st_mode))
		{
			if (!access(cmd, X_OK))
				return (cmd);
		}
		free(cmd);
	}
	return (NULL);
}

static char	*find_command_path(t_data *data)
{
	size_t	index;
	char	*cmd;
	char	**split;

	if (!data->commands[0] || !data->copied_envp)
		return (NULL);
	index = check_envp_index(data);
	if (index == (size_t)FAILURE)
		return (NULL);
	split = ft_split(&(data->copied_envp)[index][5], ':');
	if (split == NULL)
		return (NULL);
	cmd = check_access(data, split);
	if (cmd == NULL)
		return (NULL);
	free_double_array(split);
	return (cmd);
}

void	execve_command(t_data *data)
{
	extern int	g_status;
	char		*command_path;

	if (check_envp_index(data) == FAILURE)
	{
		ft_putstr_fd(data->commands[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_status = COMMAND_NOT_FOUND;
	}
	else
	{
		command_path = find_command_path(data);
		if (command_path == NULL)
		{
			ft_putstr_fd(data->commands[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			g_status = COMMAND_NOT_FOUND;
		}
		else
		{
			if (execve(command_path, data->commands, data->copied_envp) \
			== FAILURE)
				exit_with_str("execve error in execve command", EXIT_FAILURE);
		}
	}
}
