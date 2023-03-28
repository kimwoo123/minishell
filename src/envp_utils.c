/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:19:05 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 14:02:57 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_same_key(char *str, char *key)
{
	if (!ft_strncmp(str, key, strlen_before_equal(key)))
		if (strlen_before_equal(str) == strlen_before_equal(key))
			return (TRUE);
	return (FALSE);
}

char	*ft_getenv(char **array, char *str)
{
	size_t	index;
	size_t	size;
	char	*result;

	if (is_there_envp(array, str) != KEY_AND_VALUE)
		return (NULL);
	index = 0;
	while (array[index])
	{
		if (check_same_key(array[index], str))
		{
			size = strlen_before_equal(array[index]);
			result = &array[index][size + 1];
			if (result == NULL)
				exit_with_str("malloc error in ft_getenv", EXIT_FAILURE);
			return (result);
		}
		index++;
	}
	return (NULL);
}

int	is_there_envp(char **array, char *str)
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
	return (FALSE);
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
		if (check_same_key(array[i], key) == TRUE)
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
