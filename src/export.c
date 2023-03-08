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

#include "../inc/minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static void	sort_double_array(char **array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[j + i] != NULL)
		{
			if (array[j] && array[j + 1] && ft_strcmp(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	check_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	print_with_double_quotation(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	write(STDOUT_FILENO, str, (i + 1));
	write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, (str + i + 1), (ft_strlen(str) - i));
	write(STDOUT_FILENO, "\"\n", 2);
}

void	print_export(char **array)
{
	int	i;

	i = 0;
	sort_double_array(array);
	while (array[i])
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		if (check_equal_sign(array[i]))
			print_with_double_quotation(array[i]);
		else
			ft_putendl_fd(array[i], STDOUT_FILENO);
		i++;
	}
}

int	get_size_double_array(char **array)
{
	int		size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

char	**add_environment_variable(t_data *data, char *str, int size)
{
	int		i;
	char	**new_array;

	new_array = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (data->envp[i])
	{
		new_array[i] = ft_strdup(data->envp[i]);
		if (!new_array)
			ft_perror("strdup error in add_environment_variable", EXIT_FAILURE);
		i++;
	}
	new_array[i] = ft_strdup(str);
	if (!new_array)
		ft_perror("strdup error in add_environment_variable", EXIT_FAILURE);
	new_array[size + 1] = NULL;
	return (new_array);
}

void	add_environment_variables(t_data *data)
{
	int		i;
	int		array_index;
	char	**new_array;

	i = 1;
	while (data->commands[i])
	{
		array_index = get_size_double_array(data->envp);
		new_array = add_environment_variable(data, data->commands[i], array_index);
		if (!new_array)
			ft_perror("error in add_environment_variables", EXIT_FAILURE);
		free_double_array(data->envp);
		data->envp = new_array;
		i++;
	}
}

/*
1. size check double array
2. malloc
3. strdup array
4. add new one
5. put NULL on last array
*/

int	export_command(t_data *data)
{	// envp가 NULL 일 수 있을까? 만약 NULL 이라면 할당해서 진행해야할까?
	// if (data->envp == NULL)
	// 	return (0);
	if (data->commands[1] == NULL)
		print_export(data->envp);
	else
		add_environment_variables(data);
	return (0);
}
