/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:18 by chajung           #+#    #+#             */
/*   Updated: 2023/03/02 14:19:19 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	check_index(char **array)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (array[i])
	{
		if (array[i][0] != '-')
			return (i);
		j = 1;
		while (array[i][j])
		{
			if (array[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	echo_command(char **array)
{
	size_t	index;
	int		size;
	int		flag;

	flag = 0;
	index = check_index(array);
	if (index == 1)
		flag = 1;
	size = get_size_double_array(array);
	while (array[index])
	{
		write(STDOUT_FILENO, array[index], ft_strlen(array[index]));
		if (index < size - 1)
			write(STDOUT_FILENO, " ", 1);
		index++;
	}
	if (flag)
		write(STDIN_FILENO, "\n", 1);
	return (SUCCESS);
}
