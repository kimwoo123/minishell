/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:54:38 by chajung           #+#    #+#             */
/*   Updated: 2023/03/12 12:54:42 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	**set_environment_variable(char **envp)
{
	char	**temp;
	char	**array;

	temp = copy_double_array(envp);
	if (!temp)
		return (NULL);
	array = delete_environment_variable(temp, "OLDPWD");
	if (!array)
		return (NULL);
	free_double_array(temp);
	temp = array;
	array = add_environment_variable(temp, "OLDPWD");
	if (!array)
		return (NULL);
	free_double_array(temp);
	return (array);
}

void	init_data(int argc, char **argv, char **envp, t_data *data)
{
	(void)argc;
	(void)argv;
	data->envp = envp;
	data->copied_envp = set_environment_variable(envp);
	if (data->copied_envp == NULL)
		exit_with_str("copy error in set environment", EXIT_FAILURE);
}
