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
		return (1);
	else if (!ft_strncmp(data->commands[0], "unset", ft_strlen(data->commands[0])))
		return (1);
	else if (!ft_strncmp(data->commands[0], "env", ft_strlen(data->commands[0])))
		return (1);
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
	else if (is_builtin(data))
	{
		return (0);
	}
	else
		is_not_builtin(data);
	return (0);
}

void	init_data(int argc, char **argv, char **envp, t_data *data)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*command_line;

	init_data(argc, argv, envp, &data);
	while (1)
	{
		command_line = readline("minishell> ");
		if (command_line != NULL) //need this?
		{
			data.commands = ft_split(command_line, ' ');
			if (data.commands == NULL)
				ft_perror("split error in main", EXIT_FAILURE);
			parsing_command_line(&data);
			add_history(command_line);
			free (command_line);
			command_line = NULL;
		}
	}
	return (0);
}
