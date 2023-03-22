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

#include "minishell.h"

void	exit_with_str(const char *str, int exit_code)
{
	ft_putendl_fd((char *)str, STDERR_FILENO);
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
		exit_with_str("open error", EXIT_FAILURE);
	return (fd);
}

void	ft_close(int fd)
{
	if (close(fd) == FAILURE)
		exit_with_str("close error", EXIT_FAILURE);
}

int	ft_dup(int old_fd)
{
	int	new_fd;

	new_fd = dup(old_fd);
	if (new_fd == FAILURE)
		exit_with_str("dup2 error", EXIT_FAILURE);
	return (new_fd);
}

// pid_t	ft_fork(pid_t *pid)
// {
// 	*pid = fork();
// 	if (*pid == FAILURE)
// 		exit_with_str("fork error", EXIT_FAILURE);
// }

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
// 			exit_with_str("strjoin error in ft_chdir function", EXIT_FAILURE);
// 		perror(error_str);
// 	}
// }
