/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:49:11 by chajung           #+#    #+#             */
/*   Updated: 2023/03/05 11:49:13 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	pipe(t_data *data)
// {
// 	pid_t	pid;
// 	int		pipe_fd[2];

// 	if (pipe(pipe_fd) == FAILURE)
// 		ft_perror("pipe error in pipe", EXIT_FAILURE);
// 	pid = fork();
// 	if (pid == FAILURE)
// 		ft_perror("fork error in pipe", EXIT_FAILURE);
// 	if (pid == CHILD_PROCESS)
// 	{
// 		close(pipe_fd[STDIN_FILENO]);
// 		dup2(pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
// 		close(pipe_fd[STDOUT_FILENO]);
// 	}
// 	else
// 	{
// 		close(pipe_fd[STDOUT_FILENO]);
// 		dup2(pipe_fd[STDIN_FILENO], STDIN_FILENO);
// 		close(pipe_fd[STDIN_FILENO]);
// 		waitpid(pid, NULL, WNOHANG);
// 	}
// 	return (1);
// }

// static char	*find_command_path_test01(t_data *data)
// {
// 	int		i;
// 	char	*cmd;
// 	char	**split;

// 	if (!data->commands[0] || !data->envp)
// 		return (NULL);
// 	if (!access(data->commands[0], X_OK))
// 		return (data->commands[0]);
// 	while (ft_strncmp(*data->envp, "PATH=", ft_strlen("PATH=")))
// 		data->envp++;
// 	if (ft_strncmp(*data->envp, "PATH=", ft_strlen("PATH=")))
// 		return (NULL);
// 	split = ft_split(&(*data->envp)[5], ':');
// 	if (split == NULL)
// 		ft_perror("split error", EXIT_FAILURE);
// 	i = -1;
// 	while (split[++i])
// 	{
// 		cmd = ft_strjoin_wslash(split[i], data->commands[0]);
// 		if (!access(cmd, X_OK))
// 			break ;
// 		free(cmd);
// 	}
// 	free_double_array(split);
// 	if (access(cmd, X_OK))
// 		return (NULL);
// 	return (cmd);
// }

// static char	*find_command_path_test34(t_data *data)
// {
// 	int		i;
// 	char	*cmd;
// 	char	**split;

// 	if (!data->commands[3] || !data->envp)
// 		return (NULL);
// 	if (!access(data->commands[3], X_OK))
// 		return (data->commands[3]);
// 	while (ft_strncmp(*data->envp, "PATH=", ft_strlen("PATH=")))
// 		data->envp++;
// 	if (ft_strncmp(*data->envp, "PATH=", ft_strlen("PATH=")))
// 		return (NULL);
// 	split = ft_split(&(*data->envp)[5], ':');
// 	if (split == NULL)
// 		ft_perror("split error", EXIT_FAILURE);
// 	i = -1;
// 	while (split[++i])
// 	{
// 		cmd = ft_strjoin_wslash(split[i], data->commands[3]);
// 		if (!access(cmd, X_OK))
// 			break ;
// 		free(cmd);
// 	}
// 	free_double_array(split);
// 	if (access(cmd, X_OK))
// 		return (NULL);
// 	return (cmd);
// }

// static int	execute_command_test01(t_data *data)
// {
// 	char	*command_path;
// 	char	**params; // for test

// 	params = (char **)malloc(sizeof(char *) * 3);
// 	params[0] = ft_strdup(data->commands[0]);
// 	params[1] = ft_strdup(data->commands[1]);
// 	params[2] = NULL;

// 	command_path = find_command_path_test01(data);
// 	if (command_path == NULL)
// 	{
// 		printf("%s: command not found\n", data->commands[0]);
// 		return (1);
// 	}
// 	else
// 	{
// 		if (execve(command_path, params, data->envp) == FAILURE)
// 			ft_perror("execve error", EXIT_FAILURE);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	execute_command_test34(t_data *data)
// {
// 	char	*command_path;
// 	char	**params; // for test

// 	params = (char **)malloc(sizeof(char *) * 3);
// 	params[0] = ft_strdup(data->commands[3]);
// 	params[1] = ft_strdup(data->commands[4]);
// 	params[2] = NULL;

// 	command_path = find_command_path_test34(data);
// 	if (command_path == NULL)
// 	{
// 		printf("%s: command not found\n", data->commands[3]);
// 		return (1);
// 	}
// 	else
// 	{
// 		if (execve(command_path, params, data->envp) == FAILURE)
// 			ft_perror("execve error", EXIT_FAILURE);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	pipe_test(t_data *data)
// {
// 	pid_t	pid;
// 	int		pipe_fd[2];

// 	data->cmd_counts -= 1;
// 	if (data->cmd_counts > 0)
// 	{
// 		if (pipe(pipe_fd) == FAILURE)
// 			ft_perror("pipe error in pipe", EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == FAILURE)
// 		ft_perror("fork error in pipe", EXIT_FAILURE);
// 	if (pid == CHILD_PROCESS)
// 	{
// 		if (data->cmd_counts == 0)
// 		{
// 			close(pipe_fd[STDIN_FILENO]);
// 			dup2(data->dup_stdout, STDOUT_FILENO);
// 			close(pipe_fd[STDOUT_FILENO]);
// 			execute_command_test34(data);
// 			exit(EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			close(pipe_fd[STDIN_FILENO]);
// 			dup2(pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
// 			close(pipe_fd[STDOUT_FILENO]);
// 			execute_command_test01(data);
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// 	else
// 	{
// 		if (data->cmd_counts == 0)
// 		{
// 			close(pipe_fd[STDOUT_FILENO]);
// 			dup2(data->dup_stdin, STDIN_FILENO);
// 			close(pipe_fd[STDIN_FILENO]);
// 		}
// 		else
// 		{
// 			close(pipe_fd[STDOUT_FILENO]);
// 			dup2(pipe_fd[STDIN_FILENO], STDIN_FILENO);
// 			close(pipe_fd[STDIN_FILENO]);
// 		}
// 	}
// 	wait(&pid);
// 	if (data->cmd_counts > 0)
// 		pipe_test(data);
// 	return (1);
// }

// int	parsing_command_line_test(t_data *data)
// {
// 	pid_t	pid;
	
// 	if (data->commands[0] == NULL)
// 		rl_on_new_line();
// 	else if (!ft_strncmp(data->commands[0], "<<", ft_strlen(data->commands[0])))
// 		here_doc(data);
// 	else if (data->cmd_counts > 1)
// 		pipe_test(data);
// 	else
// 	{
// 		if (is_builtin(data))
// 			return (0);
// 		else
// 			is_not_builtin(data);
// 	}
// 	return (0);
// }
