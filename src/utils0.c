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

int	is_equal_to(char *str1, char *str2)
{
	if (!ft_strncmp(str1, str2, ft_strlen(str2)))
		if (ft_strlen(str1) == ft_strlen(str2))
			return (SAME);
	return (NOT_SAME);
}

/* TEST */
void	print_all_arguments(int argc, char **argv, char **envp)
{
	int	i;

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
void	print_all_argument_value(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		printf("argv[%d]: %s\n", i, argv[i]);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
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

void	ft_wait(int *wstatus)
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

// void	ft_chdir(const char *path, const char *cmd)
// {
// 	char	*error_str;

// 	if (chdir(path) == FAILURE)
// 	{
// 		if (cmd == NULL)
// 			return ;
// 		error_str = ft_strjoin("bash: cd: ", cmd);
// 		if (error_str == NULL)
// 			ft_perror("strjoin error in ft_chdir function", EXIT_FAILURE);
// 		perror(error_str);
// 	}
// }

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
	size_t	index;
	int		i;
	char	*cmd;
	char	**split;

	if (!data->commands[0] || !data->envp)
		return (NULL);
	if (!access(data->commands[0], X_OK))
		return (data->commands[0]);
	index = 0;
	while (data->envp[index] && ft_strncmp(data->envp[index], "PATH=", ft_strlen("PATH=")))
		data->envp++;
	if (!data->envp[index] || ft_strncmp(data->envp[index], "PATH=", ft_strlen("PATH=")))
	{
		printf("No such file or directory\n");
		return (NULL);
	}
	// if (*data->envp && ft_strncmp(*data->envp, "PATH=", ft_strlen("PATH=")))
	// {
	// 	printf("No such file or directory\n");
	// 	return (NULL);
	// }
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

char	**copy_double_array(char **origin_array)
{
	int		i;
	int		size;
	char	**copied_array;

	size = 0;
	while (origin_array[size])
		size++;
	copied_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copied_array)
		ft_perror("malloc error in copy double array", EXIT_FAILURE);
	i = 0;
	while (origin_array[i])
	{
		copied_array[i] = ft_strdup(origin_array[i]);
		if (!copied_array)
			ft_perror("strdup error in copy double array", EXIT_FAILURE);
		i++;
	}
	copied_array[i] = NULL;
	return (copied_array);
}


size_t	ft_strlen_before_equal_sign(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '=')
			return (index);
		index++;
	}
	return (index);
}

int	get_size_double_array(char **array)
{
	size_t	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

void	print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putendl_fd(array[i], STDOUT_FILENO);
		i++;
	}
}

int	ft_getenv(char **array, char *str)
{
	size_t	index;

	index = 0;
	while (array[index])
	{
		if (!ft_strncmp(array[index], str, ft_strlen_before_equal_sign(str)))
		{
			if (array[index][ft_strlen_before_equal_sign(str)] == '=')
				return (KEY_AND_VALUE);
			if (array[index][ft_strlen_before_equal_sign(str)] == '\0')
				return (ONLY_KEY);
		}
		index++;
	}
	return (NOT_FOUND);
}
