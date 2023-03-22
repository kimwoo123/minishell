/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:23:19 by chajung           #+#    #+#             */
/*   Updated: 2023/03/12 09:23:20 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_command(t_data *data)
{
	size_t	index;
	char	**array;

	index = 1;
	while (data->commands[index])
	{
		if (is_there_envp(data->copied_envp, \
			data->commands[index]) == KEY_AND_VALUE \
		|| is_there_envp(data->copied_envp, data->commands[index]) == ONLY_KEY)
		{
			array = delete_environment_variable(data->copied_envp, \
				data->commands[index]);
			if (!array)
				exit_with_str("malloc error in unset command", EXIT_FAILURE);
			free_double_array(data->copied_envp);
			data->copied_envp = array;
		}
		index++;
	}
}
