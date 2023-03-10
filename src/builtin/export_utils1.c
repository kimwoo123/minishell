/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:37:58 by chajung           #+#    #+#             */
/*   Updated: 2023/03/10 12:37:59 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_not_vaild_identifier(char *str)
{
	write(STDOUT_FILENO, "bash: export: '", ft_strlen("bash: export: '"));
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "': not a valid identifier\n", \
		ft_strlen("': not a valid identifier\n"));
}

static int	change_environment_variable(char **array, char *str)
{
	size_t	index;
	char	*key;
	char	*temp;

	index = 0;
	while (array[index])
	{
		if (!ft_strncmp(array[index], str, ft_strlen_before_equal_sign(str)))
		{
			if ((array[index][ft_strlen_before_equal_sign(str)] == '=') \
			|| (array[index][ft_strlen_before_equal_sign(str)] == '\0'))
			{
				temp = array[index];
				array[index] = ft_strdup(str);
				free(temp);
				return (SUCCESS);
			}
		}
		index++;
	}
	return (FAILURE);
}

int	copy_additional_arguments(t_data *data, char **array, size_t *array_index)
{
	size_t	argument_index;

	argument_index = 0;
	while (data->commands[++argument_index])
	{
		if (data->commands[argument_index][0] == '=')
			print_not_vaild_identifier(data->commands[argument_index]);
		else if (ft_getenv(array, data->commands[argument_index]) == NOT_FOUND)
		{
			array[*array_index] = ft_strdup(data->commands[argument_index]);
			if (!array[*array_index])
				return (FAILURE);
			(*array_index)++;
		}
		else if (ft_getenv(array, data->commands[argument_index]) != NOT_FOUND \
		&& check_equal_sign(data->commands[argument_index]) == FOUND)
		{
			if (change_environment_variable(array, \
				data->commands[argument_index]) == FAILURE)
				return (FAILURE);
		}
	}
	array[*array_index] = NULL;
	return (SUCCESS);
}

int	copy_origin_arguments(t_data *data, char **array, size_t *index)
{
	while (data->copied_envp[*index])
	{
		array[*index] = ft_strdup(data->copied_envp[*index]);
		if (!array[*index])
			return (FAILURE);
		(*index)++;
	}
	array[*index] = NULL;
	return (SUCCESS);
}

char	**alloc_double_array(t_data *data, size_t *index)
{
	char	**array;
	size_t	origin_size;
	size_t	add_size;

	origin_size = get_size_double_array(data->copied_envp);
	add_size = get_size_double_array(&data->commands[1]);
	array = ft_calloc((origin_size + add_size + 1), sizeof(char *));
	if (!array)
		ft_perror("error in alloc_double_array", EXIT_FAILURE);
	return (array);
}
