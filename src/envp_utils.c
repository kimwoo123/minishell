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

#include "../inc/minishell.h"

static int	check_same_key(char *str, char *key)
{
	if (!ft_strncmp(str, key, ft_strlen_before_equal_sign(key)))
	{
		if (ft_strlen_before_equal_sign(str) \
			== ft_strlen_before_equal_sign(key))
			return (FOUND);
	}
	return (NOT_FOUND);
}

char	**delete_environment_variable(char **array, char *key)
{
	char	**new_array;
	size_t	i;
	size_t	j;

	new_array = (char **)malloc(sizeof(char *) \
		* get_size_double_array(array));
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
	new_array[j] = NULL;
	return (new_array);
}

char	**add_environment_variable(char **array, char *key)
{
	char	**new_array;
	size_t	size;
	size_t	index;

	size = get_size_double_array(array);
	new_array = (char **)malloc(sizeof(char *) * (size + 2));
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
	array[size + 1] = NULL;
	return (new_array);
}