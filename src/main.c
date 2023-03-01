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

static char	*ft_strjoin_wslash(char *str1, char *str2)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(str1, "/");
	new_str = ft_strjoin(temp, str2);
	free(temp);
	return (new_str);
}

static char	*find_command_path(t_data *data)
{
	int		i;
	char	*cmd;
	char	**split;

	if (!data->commands[0] || !data->envp)
		return (NULL);
	if (!access(data->commands[0], X_OK))
		return (data->commands[0]);
	while (ft_strncmp(*data->envp, "PATH=", ft_strlen("PATH=")))
		data->envp++;
    if (ft_strncmp(*data->envp, "PATH=", ft_strlen("PATH=")))
        return (NULL);
	split = ft_split(&(*data->envp)[5], ':');
	if (split == NULL)
		ft_perror("split error", EXIT_FAILURE);
	i = -1;
	while (split[++i])
	{
		cmd = ft_strjoin_wslash(split[i], data->commands[0]);
		if (!access(cmd, X_OK))
			break ;
		free(cmd);
	}
	free_double_array(split);
	if (access(cmd, X_OK))
        return (NULL);
	return (cmd);
}

static char	*find_home_path(t_data *data)
{
	int		i;
	char	*cmd;
	char	**split;

	if (!data->commands[0] || !data->envp)
		return (NULL);
	while (ft_strncmp(*data->envp, "HOME=", ft_strlen("HOME=")))
		data->envp++;
    if (ft_strncmp(*data->envp, "HOME=", ft_strlen("HOME=")))
        return (NULL);
    return (&(*data->envp)[5]);
}

// void	proc_execve(char **argv, char **envp, t_data *data)
// {
// 	char	**params;
// 	char	*cmd;

// 	params = ft_split(argv[data->index], ' ');
// 	if (!params)
// 		ft_perror("split error", EXIT_FAILURE);
// 	cmd = find_command_path(params[0], envp);
// 	if (!cmd)
// 		ft_perror("command not found", 127);
// 	if (execve(cmd, params, envp) == -1)
// 		ft_perror("execve error", EXIT_FAILURE);
// }

int execute_command(t_data *data)
{
    char    *command_path;
    
    if (!ft_strncmp(data->commands[0], "exit", ft_strlen("exit")))
        return (-1);
    command_path = find_command_path(data);
    if (command_path == NULL)
    {
        printf("%s: command not found\n", data->commands[0]);
    }
    else
    {
        if (execve(command_path, data->commands, data->envp) == FAILURE)
    	    ft_perror("execve error", EXIT_FAILURE);
    }
    return (0);
}

int pwd_command(t_data *data)
{
    char    *path;

    path = getcwd(NULL, 0);
    if (path == NULL)
        ft_perror("pwd error", EXIT_FAILURE);
    printf("%s\n", path);
    free(path);
    path = NULL;
    return (0);
}

int cd_command(t_data *data)
{
    char    *path;

    if (data->commands[1] == NULL || !ft_strncmp(data->commands[1], "~", ft_strlen("~")))
    {
        path = find_home_path(data);
        if (path == NULL)
            ft_perror("cd error", EXIT_FAILURE);
        chdir(path);
        return (1);
    }
    else
    {
        if (!ft_strncmp(data->commands[1], ".", ft_strlen(".")))
            return (1); // is ok?
        // else if (!ft_strncmp(data->commands[1], "..", ft_strlen("..")))
        //     chdir("~");
        // else
        //     chdir(data->commands[1]);
    }
    // buffer = getcwd(NULL, 0);
    // if (buffer == NULL)
    //     ft_perror("cd error", EXIT_FAILURE);
    // printf("%s\n", buffer);
    // free(buffer);
    // buffer = NULL;
    return (0);
}

int	is_builtin(t_data *data)
{
    if (!ft_strncmp(data->commands[0], "echo", ft_strlen("echo")))
        return (1);
    else if (!ft_strncmp(data->commands[0], "cd", ft_strlen("cd")))
    {
        cd_command(data);
        return (1);
    }
    else if (!ft_strncmp(data->commands[0], "pwd", ft_strlen("pwd")))
    {
        pwd_command(data);
        return (1);
    }
    else if (!ft_strncmp(data->commands[0], "export", ft_strlen("export")))
        return (1);
    else if (!ft_strncmp(data->commands[0], "unset", ft_strlen("unset")))
        return (1);
    else if (!ft_strncmp(data->commands[0], "env", ft_strlen("env")))
        return (1);
    else if (!ft_strncmp(data->commands[0], "exit", ft_strlen("exit")))
        return (1);
	return (0);
}

// int	is_builtin(int argc, char **argv, char **envp, char **commands)
// {
//     if (!ft_strncmp(commands[0], "echo", ft_strlen("echo")) \
// 		|| !ft_strncmp(commands[0], "cd", ft_strlen("cd")) \
// 		|| !ft_strncmp(commands[0], "pwd", ft_strlen("pwd")) \
// 		|| !ft_strncmp(commands[0], "export", ft_strlen("export")) \
// 		|| !ft_strncmp(commands[0], "unset", ft_strlen("unset")) \
// 		|| !ft_strncmp(commands[0], "env", ft_strlen("env")) \
// 		|| !ft_strncmp(commands[0], "exit", ft_strlen("exit")))
// 	{
// 		// printf("%s: shell built-in command\n", commands[0]);
// 		return (1);
// 	}
// 	return (0);
// }

int is_not_builtin(t_data *data)
{
    pid_t   pid;
    
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

int parsing_command_line(t_data *data)
{
    if (data->commands == NULL || data->commands[0] == NULL)
        printf("commands are NULL in parsing function\n");
        // ft_perror("commands are NULL in parsing function", EXIT_FAILURE);
    else if (is_builtin(data))
	{
		if (!ft_strncmp(data->commands[0], "exit", ft_strlen("exit")))
        	return (-1);
	}
    else
        is_not_builtin(data);
    return (0);
}

void    init_data(int argc, char **argv, char **envp, t_data *data)
{
    data->argc = argc;
    data->argv = argv;
    data->envp = envp;
}

int main(int argc, char **argv, char **envp)
{
    t_data  data;
    char    *command_line;

    init_data(argc, argv, envp, &data);
    while (1)
    {
        command_line = readline("minishell> ");
        if (command_line != NULL) //need this?
        {
            data.commands = ft_split(command_line, ' ');
            if (data.commands == NULL)
                ft_perror("split error in main", EXIT_FAILURE);
            if (parsing_command_line(&data) == FAILURE)
            {
                printf("exit\n");
                exit(EXIT_SUCCESS);
            }
            add_history(command_line);
        }
    }
    return (0);
}
