/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:15:25 by chajung           #+#    #+#             */
/*   Updated: 2023/03/08 14:15:30 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_export(char **array)
{
	char	**new_array;
	size_t	index;

	new_array = copy_double_array(array);
	sort_double_array(new_array);
	index = 0;
	while (new_array[index])
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		if (check_equal_sign(new_array[index]))
			print_with_double_quotation(new_array[index]);
		else
		{
			write(STDOUT_FILENO, new_array[index], ft_strlen(new_array[index]));
			write(STDOUT_FILENO, "\n", 1);
		}
		index++;
	}
	free_double_array(new_array);
}

static char	**add_environment_variables(t_data *data)
{
	char	**array;
	size_t	index;

	index = 0;
	array = alloc_double_array(data, &index);
	if (!array)
		ft_perror("error in add_environment_variables", EXIT_FAILURE);
	if (copy_origin_arguments(data, array, &index) == FAILURE)
		ft_perror("error in add_environment_variable", EXIT_FAILURE);
	if (copy_additional_arguments(data, array, &index) == FAILURE)
		ft_perror("error in add_environment_variable", EXIT_FAILURE);
	return (array);
}

int	export_command(t_data *data)
{
	char	**array;

	if (data->copied_envp == NULL)
		return (0);
	else if (data->commands[1] == NULL)
		print_export(data->copied_envp);
	else
	{
		array = add_environment_variables(data);
		if (!array)
			ft_perror("error in add_environment_variables", EXIT_FAILURE);
		free_double_array(data->copied_envp);
		data->copied_envp = array;
	}
	return (0);
}
