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

#include "../inc/minishell.h"

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

int	is_builtin(t_data *data)
{
	if (!ft_strncmp(data->commands[0], "echo", ft_strlen(data->commands[0])))
	{
		echo_command(data);
		return (1);
	}
	else if (!ft_strncmp(data->commands[0], "cd", ft_strlen(data->commands[0])))
	{
		cd_command(data);
		return (1);
	}
	else if (!ft_strncmp(data->commands[0], "pwd", ft_strlen(data->commands[0])))
	{
		pwd_command(data);
		return (1);
	}
	else if (!ft_strncmp(data->commands[0], "export", ft_strlen(data->commands[0])))
	{
		export_command(data);
		return (1);
	}
	else if (!ft_strncmp(data->commands[0], "unset", ft_strlen(data->commands[0])))
		return (1);
	else if (!ft_strncmp(data->commands[0], "env", ft_strlen(data->commands[0])))
	{
		env_command(data);
		return (1);
	}
	else if (!ft_strncmp(data->commands[0], "exit", ft_strlen(data->commands[0])))
	{
		exit_command(data);
		return (1);
	}
	return (0);
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
	else if (!ft_strncmp(data->commands[0], "<<", ft_strlen(data->commands[0])))
		here_doc(data);
	else if (is_builtin(data))
		return (0);
	else
		is_not_builtin(data);
	return (0);
}

void	init_data(int argc, char **argv, char **envp, t_data *data)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->cmd_counts = 1;
	data->dup_stdin = dup(STDIN_FILENO);
	data->dup_stdout = dup(STDOUT_FILENO);
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
		parsing_command_line_test(&data);
		// add_history(command_line);
		// dprintf(2, "command: [%s]\n", command_line);
		// dprintf(2, "STDIN: %d\n", STDIN_FILENO);
		// dprintf(2, "STDOUT: %d\n", STDOUT_FILENO);
		// dprintf(2, "data.std_in: %d\n", data.dup_stdin);
		// dprintf(2, "data.std_out: %d\n", data.dup_stdout);
		free (command_line);
	}
	// ft_dup2(STDIN_FILENO, data.dup_stdin);
	// ft_dup2(STDOUT_FILENO, data.dup_stdout);
	return (0);
}
