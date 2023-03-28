/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:05:09 by chajung           #+#    #+#             */
/*   Updated: 2023/03/10 12:05:12 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	print_not_vaild_identifier(char *str)
{
	set_status(EXIT_FAILURE);
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static int	ft_strcmp(char *s1, char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] || s2[index])
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

void	sort_double_array(char **array)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[j + i] != NULL)
		{
			if (array[j] && array[j + 1] \
			&& ft_strcmp(array[j], array[j + 1]) > 0)
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

int	check_equal_sign(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '=')
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void	print_with_double_quotation(char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '=')
		index++;
	write(STDOUT_FILENO, str, (index + 1));
	write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, (str + index + 1), (ft_strlen(str) - index));
	write(STDOUT_FILENO, "\"\n", 2);
}
