/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:30:35 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 16:30:36 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_redir_exec(t_data *data)
{
	if (data->last_cmd != TRUE)
	{
		if (close(data->pipe_fd[STDIN_FILENO]) == FAILURE)
			return (FAILURE);
		if (dup2(data->pipe_fd[STDOUT_FILENO], STDOUT_FILENO) == FAILURE)
			return (FAILURE);
		if (close(data->pipe_fd[STDOUT_FILENO]) == FAILURE)
			return (FAILURE);
	}
	if (is_builtin(data->commands[0]) == TRUE)
		execve_builtin(data);
	else
		execve_command(data);
	return (SUCCESS);
}

static int	parent_redir_wait(t_data *data, pid_t pid)
{
	extern int	g_status;

	if (data->last_cmd != TRUE)
	{
		if (close(data->pipe_fd[STDOUT_FILENO]) == FAILURE)
			return (FAILURE);
		if (dup2(data->pipe_fd[STDIN_FILENO], STDIN_FILENO) == FAILURE)
			return (FAILURE);
		if (close(data->pipe_fd[STDIN_FILENO]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	do_fork(t_data *data)
{
	extern int	g_status;
	pid_t		pid;

	pid = fork();
	if (pid == FAILURE)
		exit_with_str("fork error", EXIT_FAILURE);
	if (pid == CHILD_PROCESS)
	{
		if (child_redir_exec(data) == FAILURE)
			exit_with_str("child redir error in fork", EXIT_FAILURE);
		exit(g_status);
	}
	else
	{
		if (parent_redir_wait(data, pid) == FAILURE)
			exit_with_str("parent redir error in fork", EXIT_FAILURE);
	}
}
