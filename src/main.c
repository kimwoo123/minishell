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

char	**free_double_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
	return (NULL);
}

static char	*ft_strjoin_wslash(char *str1, char *str2)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(str1, "/");
	new_str = ft_strjoin(temp, str2);
	free(temp);
	return (new_str);
}

static char	*find_command_path(char *argv, char **envp)
{
	int		i;
	char	*cmd;
	char	**split;

	if (!argv || !envp)
		return (NULL);
	if (access(argv, X_OK) == 0)
		return (argv);
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	split = ft_split(&(*envp)[5], ':');
	if (split == NULL)
		// ft_perror("split error", EXIT_FAILURE);
        return (NULL);
	i = -1;
	while (split[++i])
	{
		cmd = ft_strjoin_wslash(split[i], argv);
		if (access(cmd, X_OK) == 0)
			break ;
		free(cmd);
	}
	free_double_array(split);
    // Seg fault occurs using below codes
	if (access(cmd, X_OK))
        return (NULL);
	return (cmd);
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

static void    print_arg(int argc, char **argv, char **envp)
{
    int i;

    i = -1;
    printf("argc: %d\n", argc);
    while (++i < argc)
        printf("argv[%d]: %s\n", i, argv[i]);
    printf("argv[%d]: %s\n", i, argv[i]);
    i = -1;
    while (envp[++i])
        printf("envp[%d]: %s\n", i, envp[i]);
}

static void    print_cmd(char **argv)
{
    int i;

    i = -1;
    while (argv[++i])
        printf("argv[%d]: %s\n", i, argv[i]);
    
}

int parsing_command_line(int argc, char **argv, char **envp, char **commands)
{
    char    *cmd_wpath;
    
    if (ft_strncmp(commands[0], "exit", ft_strlen("exit")) == 0)
        return (-1);
    // cmd_wpath = find_command_path(commands[0], envp);
    // printf("%s\n", cmd_wpath);
    else if (cmd_wpath == find_command_path(commands[0], envp))
    {
        if (execve(cmd_wpath, commands, envp) == -1)
            return (1);
		    // ft_perror("execve error", EXIT_FAILURE);
    }
    // else
    // {
    //     printf("%s\n", cmd_wpath);
    // }
    // is_command_file
    // is_buit_in_command
    return (0);
}

int	is_built_in(int argc, char **argv, char **envp, char **commands)
{
	if (!ft_strncmp(commands[0], "echo", ft_strlen("echo")) \
		|| !ft_strncmp(commands[0], "cd", ft_strlen("cd")) \
		|| !ft_strncmp(commands[0], "pwd", ft_strlen("pwd")) \
		|| !ft_strncmp(commands[0], "export", ft_strlen("export")) \
		|| !ft_strncmp(commands[0], "unset", ft_strlen("unset")) \
		|| !ft_strncmp(commands[0], "env", ft_strlen("env")) \
		|| !ft_strncmp(commands[0], "exit", ft_strlen("exit")))
	{
		printf("%s: shell built-in command\n", commands[0]);
		return (1);
	}
	return (0);
}

int waiting_commands(int argc, char **argv, char **envp, char **commands)
{
    pid_t   pid;
    
    if (is_built_in(argc, argv, envp, commands))
	{
		if (!ft_strncmp(commands[0], "exit", ft_strlen("exit")))
        	return (-1);
	}
    else
    {
        pid = fork();
        if (pid == -1)
        {
            // need to fix
            printf("fork error\n");
            exit(1);
        }
        if (pid == 0)
        {
            parsing_command_line(argc, argv, envp, commands);
            return (0);
        }
        else
        {
            wait(0);
        }
    }
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    char *command_line;
    char **splited_command_line;

    while (1)
    {
        command_line = readline("minishell> ");
		splited_command_line = ft_split(command_line, ' ');
        if (splited_command_line == NULL)
        {
            // need to fix
            printf("split error\n");
            exit(1);
        }
        if (waiting_commands(argc, argv, envp, splited_command_line) == -1)
        {
            // need to fix
            printf("exit\n");
            exit(0);
        }
			// printf("test\n");
			// printf("\n argc: %d\n argv: %s\n cmd: %s\n\n", argc, argv, command_line);
		// else
		// 	printf("\n%s\n\n", command_line);
        // splited_command_line = ft_split(command_line, ' ');
        // if (splited_command_line == NULL)
        // {
        //     // need to fix
        //     printf("split error\n");
        //     exit(1);
        // }
        // if (waiting_commands(argc, argv, envp, splited_command_line) == -1)
        // {
        //     // need to fix
        //     printf("exit\n");
        //     exit(0);
        // }
    }
    return (0);
}
