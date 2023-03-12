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

#include "../../inc/minishell.h"

static int	find_path_in_envp(char **envp)
{

	while (*envp && ft_strncmp(*envp, "PATH=", ft_strlen("PATH=")))
		envp++;
	if (!*envp || ft_strncmp(*envp, "PATH=", ft_strlen("PATH=")))
	{
		// printf("No such file or directory\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// bash에서 PATH 없으면 env 명령어 실행 불가
int	env_command(t_data *data)
{
	// if (data->envp != NULL)
	// 	print_double_array(data->copied_envp);
	size_t	index;

	if (data->copied_envp == NULL)
		return (0);
	index = 0;
	if (find_path_in_envp(data->copied_envp) == FAILURE)
		return (0);
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
