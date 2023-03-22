/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:28 by chajung           #+#    #+#             */
/*   Updated: 2023/03/02 14:19:29 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_argument(t_data *data)
{
	if (ft_isalpha(data->commands[1][0]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(data->commands[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		set_status(255);
		return (TRUE);
	}
	else if (ft_isdigit(data->commands[1][0]))
	{
		if (data->commands[2] != NULL)
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			set_status(EXIT_FAILURE);
		}
		else
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			set_status(ft_atoi(data->commands[1]));
		}
		return (TRUE);
	}
	return (FALSE);
}

void	exit_command(t_data *data)
{
	extern int	g_status;

	if (data->commands[1] != NULL)
	{
		check_argument(data);
		exit(g_status);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
}
