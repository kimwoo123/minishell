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

#include "../inc/minishell.h"

int	echo_command(t_data *data)
{
	if (!ft_strncmp(data->commands[1], "-n", ft_strlen("-n")))
	{
		printf("%s", data->commands[2]);
		return (1);
	}
	else
	{
		if (data->commands[1] != NULL)
			printf("%s", data->commands[1]);
		printf("\n");
		return (1);
	}
	return (0);
}
