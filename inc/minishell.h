/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:46 by chajung           #+#    #+#             */
/*   Updated: 2023/03/08 14:15:46 by wooseoki         ###   ########.fr       */
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

# define SUCCESS		0
# define FAILURE		-1
# define CHILD_PROCESS  0
# define DELIMITER "<>|"

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**commands;
	int		cmd_counts;
	int		dup_stdin;
	int		dup_stdout;
}	t_data;

typedef struct	s_node
{
	int				type;
	char			*content;
	struct s_node	*left_child;
	struct s_node	*right_child;	
}	t_node;

typedef	struct	s_stack
{
	int				type;
	char			*content;
	struct s_stack	*next;
}	t_stack;

typedef struct	s_list
{
	int				type;
	char			*content;
	struct s_list	*next;
}	t_list;

enum	e_type
{
	PIPE,
	REDIRECTION,
	WORD,
	QUOTE,
};

int	parsing_command_line_test(t_data *data);
int	is_not_builtin(t_data *data);
int	is_builtin(t_data *data);

/* built-in */
int		echo_command(t_data *data);
int		cd_command(t_data *data);
int		pwd_command(t_data *data);
int		exit_command(t_data *data);

/* heredoc */
int	here_doc(t_data *data);

/* signals */
void	set_signals(void);

/* utils0 */
void	print_all_arguments(int argc, char **argv, char **envp);
void	print_all_argument_value(char **argv);
char	**free_double_array(char **array);
void	ft_perror(const char *str, int exit_code);
int		ft_open(const char *path, int oflag, int flag);
void	ft_close(int fd);
void	ft_dup2(int old_fd, int new_fd);
// void	ft_fork(pid_t *pid);
void	ft_unlink(const char *path);
void	ft_wait(int *wstatus);
// int	do_wait(t_data *data);
// int	do_wait_bonus(t_data *data);
// void	ft_chdir(const char *path, const char *cmd);
char	*ft_strjoin_wslash(char *str1, char *str2);
char	*find_command_path(t_data *data);

/* deli_parse */
void	check_quote(const char c, char *flag);
void	seperate_meta(const char *line, size_t size, t_node *node);
void	split_space(const char *line, size_t size, t_node *node);
int	repeat_meta(const char *line, size_t index);
int	split_delimiter(const char *line, t_node *node);
void	scan_command(const char* line);
char *ft_strndup(const char *begin, size_t size);

/* tree */
void	get_token(const char *line, size_t size, t_list **list);
t_node	*create_node(int type, char *content);

#endif
