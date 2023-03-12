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

#include "../inc/minishell.h"

static char	**add_oldpwd_in_envp(char **array)
{
	char	**new_array;
	size_t	size;
	size_t	index;

	size = get_size_double_array(array);
	new_array = ft_calloc((size + 2), sizeof(char *));
	if (!new_array)
		return (NULL);
	index = 0;
	while (array[index])
	{
		new_array[index] = ft_strdup(array[index]);
		if (!new_array[index])
			return (NULL);
		index++;
	}
	new_array[index] = ft_strdup("OLDPWD");
	if (!new_array[index])
		return (NULL);
	array[size + 1] = NULL;
	return (new_array);
}

static char	**set_environment_variable(char **envp)
{
	char	**temp;
	char	**array;

	temp = copy_double_array(envp);
	if (!temp)
		ft_perror("copy_double_array error in init data", EXIT_FAILURE);
	array = delete_environment_variable(temp, "OLDPWD");
	if (!array)
		ft_perror("unset_command error in init data", EXIT_FAILURE);
	free_double_array(temp);
	temp = array;
	array = add_oldpwd_in_envp(temp);
	if (!array)
		return (NULL);
	free_double_array(temp);
	temp = NULL;
	return (array);
}

void	init_data(int argc, char **argv, char **envp, t_data *data)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->copied_envp = set_environment_variable(envp);
	if (!data->copied_envp)
		ft_perror("copy_double_array error in init data", EXIT_FAILURE);
	data->cmd_counts = 1;
	data->dup_stdin = dup(STDIN_FILENO);
	data->dup_stdout = dup(STDOUT_FILENO);
}
