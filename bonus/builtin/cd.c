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

#include "minishell_bonus.h"

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
	if (backup_working_directory(data) == FAILURE)
		exit_with_str("backup error in cd command", EXIT_FAILURE);
	if (change_directory(data) == FAILURE)
		exit_with_str("cd error in cd command", EXIT_FAILURE);
	if (change_working_directory(data) == FAILURE)
		exit_with_str("backup error in cd command", EXIT_FAILURE);
}
