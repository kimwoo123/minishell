/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:59:14 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 18:45:20 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	**free_double_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
	return (NULL);
}

static int	double_array_size(char *str, char c)
{
	int	size;

	size = 0;
	if (*str && *str != c)
		size++;
	if (*str)
		str++;
	while (*str)
	{
		if (*str != c && *(str - 1) == c)
			size++;
		str++;
	}
	return (size);
}

static int	single_array_size(char *str, char c)
{
	int	size;

	if (str == NULL)
		return (1);
	size = 0;
	if (*str == c)
		str++;
	while (*str && *str != c)
	{
		str++;
		size++;
	}
	return (size);
}

static int	make_array(char **array, char *str, char c, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = 0;
		while (*str && *str == c)
			str++;
		array[i] = (char *)malloc(sizeof(char) \
			* (single_array_size(str, c) + 1));
		if (array[i] == NULL)
			return (1);
		while (*str && *str != c)
			array[i][j++] = *str++;
		array[i][j] = '\0';
	}
	array[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**array;

	size = double_array_size((char *)s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
		return (NULL);
	if (make_array(array, (char *)s, c, size) == 1)
		return (free_double_array(array));
	return (array);
}
