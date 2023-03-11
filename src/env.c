/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:15:03 by chajung           #+#    #+#             */
/*   Updated: 2023/03/08 14:15:04 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	check_equal_sign(char *str)
// {
// 	size_t	index;

// 	index = 0;
// 	while (str[index])
// 	{
// 		if (str[index] == '=')
// 			return (FOUND);
// 		index++;
// 	}
// 	return (NOT_FOUND);
// }

// bash에서 PATH 없으면 env 명령어 실행 불가
int	env_command(t_data *data)
{
	// if (data->envp != NULL)
	// 	print_double_array(data->copied_envp);
	size_t	index;

	if (data->copied_envp == NULL)
		return (0);
	index = 0;
	while (data->copied_envp[index])
	{
		if (check_equal_sign(data->copied_envp[index]))
		{
			write(STDOUT_FILENO, data->copied_envp[index], ft_strlen(data->copied_envp[index]));
			write(STDOUT_FILENO, "\n", 1);
		}
		index++;
	}
	return (0);
}
