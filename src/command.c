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
		ft_putstr_fd(data->commands[0], STDOUT_FILENO);
		ft_putendl_fd(": command not found", STDOUT_FILENO);
		return (FAILURE);
	}
	else
	{
		if (execve(command_path, data->commands, data->envp) == FAILURE)
			ft_perror("execve error", EXIT_FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	child_redir_exec(t_data *data)
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
}

static void	parent_redir_wait(t_data *data, pid_t pid)
{
	extern int	g_status;

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

int	do_fork(t_data *data)
{
	pid_t		pid;

	pid = fork();
	if (pid == FAILURE)
		ft_perror("fork error", EXIT_FAILURE);
	if (pid == CHILD_PROCESS)
	{
		child_redir_exec(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		parent_redir_wait(data, pid);
	}
	return (0);
}
