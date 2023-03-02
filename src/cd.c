/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cd.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: chajung <chajung@student.42seoul.kr>	   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/03/02 13:08:45 by chajung		   #+#	#+#			 */
/*   Updated: 2023/03/02 13:08:47 by chajung		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static char	*find_home_path(t_data *data)
{
	if (!data->commands[0] || !data->envp)
		return (NULL);
	while (ft_strncmp(*data->envp, "HOME=", ft_strlen("HOME=")))
		data->envp++;
	if (ft_strncmp(*data->envp, "HOME=", ft_strlen("HOME=")))
		return (NULL);
	return (&(*data->envp)[5]);
}

// need to add OLDPWD and exit code
int	cd_command(t_data *data)
{
	char	*path;
	char	*temp;
	char	*pwd_path;

	if (data->commands[1] == NULL || !ft_strncmp(data->commands[1], "~", ft_strlen("~")))
	{
		temp = find_home_path(data);
		if (temp == NULL)
			ft_perror("path error in cd command", EXIT_FAILURE);
		if (data->commands[1] == NULL \
			|| !ft_strncmp(data->commands[1], "~", ft_strlen(data->commands[1])) \
			|| !ft_strncmp(data->commands[1], "~/", ft_strlen(data->commands[1])))
			ft_chdir(temp, data->commands[1]);
		else
		{
			path = ft_strjoin_wslash(temp, &data->commands[1][2]);
			if (path == NULL)
				ft_perror("strjoin_wslash error in cd command", EXIT_FAILURE);
			ft_chdir(path, data->commands[1]);
			free(path);
		}
	}
	else if (!ft_strncmp(data->commands[1], "/", ft_strlen("/")))
	{
		if (!ft_strncmp(data->commands[1], "/", ft_strlen(data->commands[1])))
			ft_chdir("/", data->commands[1]);
		else
		{
			path = ft_strjoin_wslash("/", &data->commands[1][1]);
			if (path == NULL)
				ft_perror("strjoin_wslash error in cd command", EXIT_FAILURE);
			ft_chdir(path, data->commands[1]);
			free(path);
		}
	}
	else
	{
		temp = getcwd(NULL, 0);
		if (temp == NULL)
			ft_perror("getcwd error in cd command", EXIT_FAILURE);
		path = ft_strjoin_wslash(temp, data->commands[1]);
		if (path == NULL)
			ft_perror("strjoin_wslash error in cd command", EXIT_FAILURE);
		free(temp);
		ft_chdir(path, data->commands[1]);
		free(path);
	}
	return (0);
}
