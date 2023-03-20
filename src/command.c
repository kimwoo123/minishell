/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:30:35 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 16:30:36 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_command(t_data *data)
{
	char	*command_path;

	command_path = find_command_path(data);
	if (command_path == NULL)
	{
		printf("%s: command not found\n", data->commands[0]);
		return (1);
	}
	else
	{
		if (execve(command_path, data->commands, data->envp) == FAILURE)
			ft_perror("execve error", EXIT_FAILURE);
		return (1);
	}
	return (0);
}

int	is_not_builtin(t_data *data)
{
	pid_t		pid;
	extern int	g_status;

	pid = fork();
	if (pid == FAILURE)
		ft_perror("fork error", EXIT_FAILURE);
	if (pid == CHILD_PROCESS)
	{
		if (data->last_cmd != TRUE)
		{
			ft_close(data->pipe_fd[STDIN_FILENO]);
			ft_dup2(data->pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
			ft_close(data->pipe_fd[STDOUT_FILENO]);
		}
		if (is_builtin(data->commands[0]) == TRUE)
			execve_builtin(data);
		else
			execve_command(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (data->last_cmd != TRUE)
		{
			ft_close(data->pipe_fd[STDOUT_FILENO]);
			ft_dup2(data->pipe_fd[STDIN_FILENO], STDIN_FILENO);
			ft_close(data->pipe_fd[STDIN_FILENO]);
			wait(0);
		}
		else
			waitpid(pid, &g_status, 0);
	}
	return (0);
}
