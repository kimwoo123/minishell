/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:19:05 by chajung           #+#    #+#             */
/*   Updated: 2023/03/12 14:19:06 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getenv(char **array, char *str)
{
	size_t	index;

	index = 0;
	while (array[index])
	{
		if (!ft_strncmp(array[index], str, strlen_before_equal(str)))
		{
			if (array[index][strlen_before_equal(str)] == '=')
				return (KEY_AND_VALUE);
			if (array[index][strlen_before_equal(str)] == '\0')
				return (ONLY_KEY);
		}
		index++;
	}
	return (NOT_FOUND);
}

static int	check_same_key(char *str, char *key)
{
	if (!ft_strncmp(str, key, strlen_before_equal(key)))
		if (strlen_before_equal(str) == strlen_before_equal(key))
			return (FOUND);
	return (NOT_FOUND);
}

char	**delete_environment_variable(char **array, char *key)
{
	char	**new_array;
	size_t	size;
	size_t	i;
	size_t	j;

	size = get_size_double_array(array);
	new_array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	j = 0;
	while (array[i])
	{
		if (check_same_key(array[i], key) == FOUND)
			i++;
		else
		{
			new_array[j] = ft_strdup(array[i]);
			if (!new_array[j])
				return (NULL);
			i++;
			j++;
		}
	}
	return (new_array);
}

char	**add_environment_variable(char **array, char *key)
{
	char	**new_array;
	size_t	size;
	size_t	index;

	size = get_size_double_array(array);
	new_array = (char **)ft_calloc(size + 2, sizeof(char *));
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
	new_array[index] = ft_strdup(key);
	if (!new_array[index])
		return (NULL);
	return (new_array);
}
