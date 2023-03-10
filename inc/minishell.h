/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:46 by chajung           #+#    #+#             */
/*   Updated: 2023/03/13 09:26:44 by wooseoki         ###   ########.fr       */
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
# define DELIMITER 		"<>|"

# define NOT_FOUND		0
# define ONLY_KEY		1
# define KEY_AND_VALUE	2

# define NOT_FOUND		0
# define FOUND			1

# define NOT_SAME		0
# define SAME			1

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**copied_envp;
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

/* init */
void	init_data(int argc, char **argv, char **envp, t_data *data);

/* built-in */
// int		echo_command(t_data *data);
int		cd_command(t_data *data);
int		pwd_command(t_data *data);
int		exit_command(t_data *data);
int		env_command(t_data *data);
int		export_command(t_data *data);
int		unset_command(t_data *data);
int		echo_command(char **array);

/* cd */
int		backup_working_directory(t_data *data);
int		change_working_directory(t_data *data);
void	ft_chdir(const char *path, const char *cmd);
char	*find_home_path(char **envp);

/* unset */
char	**delete_environment_variable(char **array, char *key);

/* export */
void	sort_double_array(char **array);
int		check_equal_sign(char *str);
void	print_with_double_quotation(char *str);
int		copy_additional_arguments(t_data *data, char **array, size_t *array_index);
int		copy_origin_arguments(t_data *data, char **array, size_t *index);
char	**alloc_double_array(t_data *data, size_t *index);

/* heredoc */
int	here_doc(t_data *data);

/* signals */
void	set_signals(void);

/* utils0 */
int		is_equal_to(char *str1, char *str2);
void	print_all_arguments(int argc, char **argv, char **envp);
void	print_all_argument_value(char **argv);
void	free_double_array(char **array);
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
char	**copy_double_array(char **origin_array);
size_t	ft_strlen_before_equal_sign(char *str);
int		get_size_double_array(char **array);
void	print_double_array(char **array);
int		ft_getenv(char **array, char *str);

/* envp_utils */
char	**add_environment_variable(char **array, char *key);
char	**delete_environment_variable(char **array, char *key);

/* deli_parse */
char	check_quote(const char c, char flag);
void	seperate_meta(const char *line, size_t size, t_list **node);
void	split_space(const char *line, size_t size, t_list **node);
void	search_list(t_list *list);
int		repeat_meta(const char *line, size_t index);
void	split_delimiter(const char *line, t_list **node);
void	scan_command(const char* line);
char 	*ft_strndup(const char *begin, size_t size);
int		is_space(const char c);
int		is_quote(const char c);

/* tree */
void	get_token(char const *line, size_t size, t_list **list);
t_node	*create_node(int type, char *content);

/* dollar */
size_t	get_dollar_len(char const *line);
size_t	get_dollar_index(char const *line, char *quote_flag);
size_t	double_array_size(char const *line, char *quote_flag);
void	duplicate_str(char **result, char *line, char *quote_flag);
char	**split_dollar(char const *line, size_t size);
char	*remove_quote(char const *line);
char	*convert_variable(char *str);
char	*merge_str(char **split_str);
void	free_double(char **str);
char	*convert_merge(char **split_str);
char	*convert_dollar(char const *line, size_t size);

/* free */
void	free_list(t_list **list);

#endif
