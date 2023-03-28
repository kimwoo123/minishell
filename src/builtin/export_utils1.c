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

#include "minishell_bonus.h"

static int	check_identifier(char c)
{
	if (c == ' ' || c == '=' || ft_isdigit(c))
		return (FALSE);
	if (ft_isalpha(c) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	change_environment_variable(char **array, char *str)
{
	size_t	index;
	char	*temp;

	index = 0;
	while (array[index])
	{
		if (!ft_strncmp(array[index], str, strlen_before_equal(str)))
		{
			if ((array[index][strlen_before_equal(str)] == '=') \
			|| (array[index][strlen_before_equal(str)] == '\0'))
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

int	copy_additional_args(t_data *data, char **array, size_t *array_index)
{
	size_t	argument_index;

	argument_index = 0;
	while (data->commands[++argument_index])
	{
		if (check_identifier(data->commands[argument_index][0]) == FALSE)
			print_not_vaild_identifier(data->commands[argument_index]);
		else if (is_there_envp(array, data->commands[argument_index]) == FALSE)
		{
			array[*array_index] = ft_strdup(data->commands[argument_index]);
			if (!array[*array_index])
				return (FAILURE);
			(*array_index)++;
		}
		else if (is_there_envp(array, data->commands[argument_index]) != FALSE \
		&& check_equal_sign(data->commands[argument_index]) == TRUE)
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

char	**alloc_double_array(t_data *data)
{
	char	**array;
	size_t	origin_size;
	size_t	add_size;

	origin_size = get_size_double_array(data->copied_envp);
	add_size = get_size_double_array(&data->commands[1]);
	array = ft_calloc((origin_size + add_size + 1), sizeof(char *));
	if (!array)
		exit_with_str("malloc error in alloc double array", EXIT_FAILURE);
	return (array);
}
