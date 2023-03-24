/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:15:25 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 17:06:16 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	print_export(char **array)
{
	char	**new_array;
	size_t	index;

	new_array = copy_double_array(array);
	if (new_array == NULL)
		exit_with_str("malloc error in print export", EXIT_FAILURE);
	sort_double_array(new_array);
	index = 0;
	while (new_array[index])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (check_equal_sign(new_array[index]))
			print_with_double_quotation(new_array[index]);
		else
			ft_putendl_fd(new_array[index], STDOUT_FILENO);
		index++;
	}
	free_double_array(new_array);
}

static char	**add_environment_variables(t_data *data)
{
	char	**array;
	size_t	index;

	index = 0;
	array = alloc_double_array(data);
	if (!array)
		return (NULL);
	if (copy_origin_arguments(data, array, &index) == FAILURE)
		return (NULL);
	if (copy_additional_args(data, array, &index) == FAILURE)
		return (NULL);
	return (array);
}

void	export_command(t_data *data)
{
	char		**array;

	if (data->copied_envp == NULL)
		return ;
	else if (data->commands[1] == NULL)
		print_export(data->copied_envp);
	else
	{
		set_status(EXIT_SUCCESS);
		array = add_environment_variables(data);
		if (!array)
			exit_with_str("error in export command", EXIT_FAILURE);
		free_double_array(data->copied_envp);
		data->copied_envp = array;
	}
}
