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

#include "../inc/minishell.h"

static char	*find_home_path(t_data *data)
{
	int		i;
	char	*cmd;
	char	**split;

	if (!data->commands[0] || !data->envp)
		return (NULL);
	while (ft_strncmp(*data->envp, "HOME=", ft_strlen("HOME=")))
		data->envp++;
    if (ft_strncmp(*data->envp, "HOME=", ft_strlen("HOME=")))
        return (NULL);
    return (&(*data->envp)[5]);
}

int cd_command(t_data *data)
{
    char    *path;
    char    *pwd_path;
	char	*joined_path;

    if (data->commands[1] == NULL || !ft_strncmp(data->commands[1], "~", ft_strlen("~")))
    {
        path = find_home_path(data);
        if (path == NULL)
            ft_perror("path error in cd command", EXIT_FAILURE);
        if (!ft_strncmp(data->commands[1], "~", ft_strlen(data->commands[1])) \
            || !ft_strncmp(data->commands[1], "~/", ft_strlen(data->commands[1])))
            ft_chdir(path, data->commands[1]);
		else
		{
			joined_path = ft_strjoin_wslash(path, &data->commands[1][2]);
			if (joined_path == NULL)
            	ft_perror("strjoin_wslash error in cd command", EXIT_FAILURE);
			ft_chdir(joined_path, data->commands[1]);
        	free(joined_path);
		}
        return (1);
    }
    else if (!ft_strncmp(data->commands[1], "/", ft_strlen("/")))
    {
        if (!ft_strncmp(data->commands[1], "/", ft_strlen(data->commands[1])))
            ft_chdir("/", data->commands[1]);
		else
		{
			joined_path = ft_strjoin_wslash("/", &data->commands[1][1]);
			if (joined_path == NULL)
            	ft_perror("strjoin_wslash error in cd command", EXIT_FAILURE);
			ft_chdir(joined_path, data->commands[1]);
        	free(joined_path);
		}
        return (1);
	}
    else
    {
        pwd_path = getcwd(NULL, 0);
        if (pwd_path == NULL)
            ft_perror("getcwd error in cd command", EXIT_FAILURE);
        path = ft_strjoin_wslash(pwd_path, data->commands[1]);
		if (path == NULL)
            ft_perror("strjoin_wslash error in cd command", EXIT_FAILURE);
        free(pwd_path);
        ft_chdir(path, data->commands[1]);
        free(path);
        return (1);
    }
    return (0);
}
