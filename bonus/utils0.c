/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:56:10 by chajung           #+#    #+#             */
/*   Updated: 2023/03/01 20:56:11 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_equal_to(char *str1, char *str2)
{
	if (!ft_strncmp(str1, str2, ft_strlen(str2)))
		if (ft_strlen(str1) == ft_strlen(str2))
			return (TRUE);
	return (FALSE);
}

size_t	strlen_before_equal(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '=')
			return (index);
		index++;
	}
	return (index);
}

size_t	get_size_double_array(char **array)
{
	size_t	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

char	*ft_strjoin_wslash(char *str1, char *str2)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(str1, "/");
	if (temp == NULL)
		return (NULL);
	new_str = ft_strjoin(temp, str2);
	if (new_str == NULL)
		return (NULL);
	free(temp);
	return (new_str);
}

char	**copy_double_array(char **origin_array)
{
	int		i;
	int		size;
	char	**copied_array;

	size = 0;
	while (origin_array[size])
		size++;
	copied_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copied_array)
		return (NULL);
	i = 0;
	while (origin_array[i])
	{
		copied_array[i] = ft_strdup(origin_array[i]);
		if (!copied_array)
			return (NULL);
		i++;
	}
	copied_array[i] = NULL;
	return (copied_array);
}
