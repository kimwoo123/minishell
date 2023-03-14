/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:10 by chajung           #+#    #+#             */
/*   Updated: 2023/03/01 17:21:11 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_data *data)
{
	char	*command_path;

	command_path = find_command_path(data);
	if (command_path == NULL)
	{
		// perror(data->commands[0]);
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

int	exec_builtin(t_data *data)
{
	int	result;
	
	result = FAILURE;
	if (is_equal_to(data->commands[0], "echo") == SAME)
		result = echo_command(data->commands);
	else if (is_equal_to(data->commands[0], "cd") == SAME)
		result = cd_command(data);
	else if (is_equal_to(data->commands[0], "pwd") == SAME)
		result = pwd_command(data);
	else if (is_equal_to(data->commands[0], "export") == SAME)
		result = export_command(data);
	else if (is_equal_to(data->commands[0], "unset") == SAME)
		result = unset_command(data);
	else if (is_equal_to(data->commands[0], "env") == SAME)
		result = env_command(data);
	else if (is_equal_to(data->commands[0], "exit") == SAME)
		result = exit_command(data);
	return (result);
}

int	is_builtin(char *str)
{
	if (is_equal_to(str, "echo") == SAME \
	|| is_equal_to(str, "cd") == SAME \
	|| is_equal_to(str, "pwd") == SAME \
	|| is_equal_to(str, "export") == SAME \
	|| is_equal_to(str, "unset") == SAME \
	|| is_equal_to(str, "env") == SAME \
	|| is_equal_to(str, "exit") == SAME)
		return (FOUND);
	return (NOT_FOUND);
}

int	is_not_builtin(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILURE)
		ft_perror("fork error", EXIT_FAILURE);
	if (pid == CHILD_PROCESS)
	{
		execute_command(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_wait(NULL);
	}
	return (0);
}

int	parsing_command_line(t_data *data)
{
	if (data->commands[0] == NULL)
		rl_on_new_line();
	else if (is_equal_to(data->commands[0], "<<") == SAME)
		here_doc(data);
	else if (is_equal_to(data->commands[0], "|") == SAME)
		return (0); // PIPE
	else if (is_builtin(data->commands[0]) == FOUND)
		exec_builtin(data);
	else
		is_not_builtin(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*command_line;

	init_data(argc, argv, envp, &data);
	set_signals();
	while (1)
	{
		command_line = readline("minishell> ");
		if (command_line == NULL)
			break ;
		add_history(command_line);
		data.commands = ft_split(command_line, ' ');
		if (data.commands == NULL)
			ft_perror("split error in main", EXIT_FAILURE);
		free (command_line);
		parsing_command_line(&data);
	}
	return (0);
}
