/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:05:47 by chajung           #+#    #+#             */
/*   Updated: 2023/03/13 10:05:48 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*get_old_working_directory(void)
{
	char	*temp;
	char	*path;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (NULL);
	path = ft_strjoin("OLDPWD=", temp);
	if (!path)
		return (NULL);
	free(temp);
	temp = NULL;
	return (path);
}

static char	*get_present_working_directory(void)
{
	char	*temp;
	char	*path;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (NULL);
	path = ft_strjoin("PWD=", temp);
	if (!path)
		return (NULL);
	free(temp);
	temp = NULL;
	return (path);
}

int	backup_working_directory(t_data *data)
{
	char	*path;
	char	**temp;
	char	**new_envp;

	path = get_old_working_directory();
	if (!path)
		return (FAILURE);
	temp = delete_environment_variable(data->copied_envp, "OLDPWD");
	if (!temp)
		return (FAILURE);
	free_double_array(data->copied_envp);
	new_envp = add_environment_variable(temp, path);
	if (!new_envp)
		return (FAILURE);
	free(path);
	free_double_array(temp);
	data->copied_envp = new_envp;
	return (SUCCESS);
}

int	change_working_directory(t_data *data)
{
	char	*path;
	char	**temp;
	char	**new_envp;

	path = get_present_working_directory();
	if (!path)
		return (FAILURE);
	temp = delete_environment_variable(data->copied_envp, "PWD");
	if (!temp)
		return (FAILURE);
	free_double_array(data->copied_envp);
	new_envp = add_environment_variable(temp, path);
	if (!new_envp)
		return (FAILURE);
	free(path);
	free_double_array(temp);
	data->copied_envp = new_envp;
	return (SUCCESS);
}
