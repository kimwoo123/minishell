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

#include "minishell_bonus.h"

static int	is_int(t_data *data)
{
	int	i;

	i = 0;
	if (data->commands[1][i] == '+' || data->commands[1][i] == '-')
		i++;
	while (data->commands[1][i])
	{
		if (!ft_isdigit(data->commands[1][i]))
			return (FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	check_argument(t_data *data)
{
	extern int	g_status;

	if (is_int(data) == FAILURE)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(data->commands[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_status = 255;
		return (TRUE);
	}
	else
	{
		if (data->commands[2] != NULL)
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			g_status = EXIT_FAILURE;
		}
		else
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			g_status = ft_atoi(data->commands[1]);
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
		g_status = EXIT_SUCCESS;
		exit(g_status);
	}
}
