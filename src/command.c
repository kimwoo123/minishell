/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:31:44 by chajung           #+#    #+#             */
/*   Updated: 2023/03/21 09:31:45 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t	index;
	char	*cmd;

	index = 0;
	while (split[index])
	{
		cmd = ft_strjoin_wslash(split[index], data->commands[0]);
		if (cmd == NULL)
			return (NULL);
		if (!access(cmd, X_OK))
			break ;
		free(cmd);
		index++;
	}
	return (cmd);
}

static char	*find_command_path(t_data *data)
{
	size_t	index;
	char	*cmd;
	char	**split;

	if (!data->commands[0] || !data->copied_envp)
		return (NULL);
	if (!access(data->commands[0], X_OK))
		return (data->commands[0]);
	index = check_envp_index(data);
	if (index == FAILURE)
	{
		ft_putendl_fd("No such file or directory", STDIN_FILENO);
		return (NULL);
	}
	split = ft_split(&(data->copied_envp)[index][5], ':');
	if (split == NULL)
		return (NULL);
	cmd = check_access(data, split);
	if (cmd == NULL)
		return (NULL);
	free_double_array(split);
	if (access(cmd, X_OK))
		return (NULL);
	return (cmd);
}

void	execve_command(t_data *data)
{
	char	*command_path;

	command_path = find_command_path(data);
	if (command_path == NULL)
	{
		ft_putstr_fd(data->commands[0], STDOUT_FILENO);
		ft_putendl_fd(": command not found", STDOUT_FILENO);
	}
	else
	{
		if (execve(command_path, data->commands, data->envp) == FAILURE)
			exit_with_str("execve error in execve command", EXIT_FAILURE);
	}
}
