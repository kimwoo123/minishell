/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:46 by chajung           #+#    #+#             */
/*   Updated: 2023/03/01 17:21:47 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/inc/libft.h"

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

# define SUCCESS    	0
# define FAILURE	    -1
# define CHILD_PROCESS  0

typedef struct s_data
{
	int     argc;
    char    **argv;
    char    **envp;
    char    **commands;
}	t_data;

/* built-in */
int     cd_command(t_data *data);

/* utils0 */
void    print_all_arguments(int argc, char **argv, char **envp);
void    print_all_argument_value(char **argv);
char	**free_double_array(char **array);
void	ft_perror(const char *str, int exit_code);
int		ft_open(const char *path, int oflag, int flag);
void	ft_close(int fd);
void	ft_dup2(int old_fd, int new_fd);
// void	ft_fork(pid_t *pid);
void	ft_unlink(const char *path);
void    ft_wait(int *wstatus);
// int	do_wait(t_data *data);
// int	do_wait_bonus(t_data *data);
void	ft_chdir(const char *path, const char *cmd);
char	*ft_strjoin_wslash(char *str1, char *str2);
char	*find_command_path(t_data *data);

#endif
