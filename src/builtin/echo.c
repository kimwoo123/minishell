/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:18 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 15:52:04 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

void	echo_command(char **array)
{
	size_t	index;
	size_t	size;
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
		write(STDOUT_FILENO, "\n", 1);
	set_status(EXIT_SUCCESS);
}
