/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:56:10 by chajung           #+#    #+#             */
/*   Updated: 2023/03/01 20:56:11 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/* TEST */
void    print_all_arguments(int argc, char **argv, char **envp)
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
/* TEST */
void    print_all_argument_value(char **argv)
{
    int i;

    i = -1;
    while (argv[++i])
        printf("argv[%d]: %s\n", i, argv[i]);   
}

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

void	ft_perror(const char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

int	ft_open(const char *path, int oflag, int flag)
{
	int	fd;

	if (flag == -1)
		fd = open(path, oflag);
	else
		fd = open(path, oflag, flag);
	if (fd == FAILURE)
		ft_perror("open error", EXIT_FAILURE);
	return (fd);
}

void	ft_close(int fd)
{
	if (close(fd) == FAILURE)
		ft_perror("close error", EXIT_FAILURE);
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == FAILURE)
		ft_perror("dup2 error", EXIT_FAILURE);
}

// void	ft_fork(pid_t *pid)
// {
// 	*pid = fork();
// 	if (*pid == FAILURE)
// 		ft_perror("fork error", EXIT_FAILURE);
// }

void	ft_unlink(const char *path)
{
	if (unlink(path) == FAILURE)
		ft_perror("unlink error", EXIT_FAILURE);
}

void    ft_wait(int *wstatus)
{
    if (wait(wstatus) == FAILURE)
			ft_perror("wait error", EXIT_FAILURE);
}

// int	do_wait(t_data *data)
// {
// 	waitpid(data->pid, &data->stat, 0);
// 	while (data->index > 3)
// 	{
// 		ft_wait(NULL);
// 		data->index--;
// 	}
// 	return ((data->stat >> 8) & 0x000000ff);
// }

// int	do_wait_bonus(t_data *data)
// {
// 	waitpid(data->pid, &data->stat, 0);
// 	ft_wait(NULL);
// 	return ((data->stat >> 8) & 0x000000ff);
// }

void	ft_chdir(const char *path, const char *cmd)
{
	char	*error_str;

	if (chdir(path) == FAILURE)
	{
		if (cmd == NULL)
			return ;
		error_str = ft_strjoin("bash: cd: ", cmd);
		if (error_str == NULL)
			ft_perror("strjoin error in ft_chdir function", EXIT_FAILURE);
		perror(error_str);
	}
}


char	*ft_strjoin_wslash(char *str1, char *str2)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(str1, "/");
	new_str = ft_strjoin(temp, str2);
	free(temp);
	return (new_str);
}

char	*find_command_path(t_data *data)
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
