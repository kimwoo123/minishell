/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:46 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 10:25:15 by wooseoki         ###   ########.fr       */
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
# include <signal.h>
# include <termios.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "parse.h"
# include "structure.h"
# include "../libft/inc/libft.h"

void	search_tree_for_hd(t_data *data, t_tree *head);
void	search_tree(t_data *data, t_tree *head);

void	run_minishell(t_data *data, char *command_line);

void	exit_with_str(const char *str, int exit_code);

/* redirection */
void	do_redirection(t_data *data, t_tree *tree);

/* redirection utils */
char	*join_redirection(t_tree *tree);
int		split_redirection(t_data *data, t_tree *tree);

/* tree */
void	make_nice_name(t_data *data, char *command_line);

/* tree utils */
t_tree	*create_root(void);
t_tree	*create_tree(int type, char *content, t_tree *left, t_tree *right);
t_tree	*make_tree(t_list **node);
void	add_pipe(t_tree **head);
void	add_commands(t_tree **head, t_list *node);
void	add_redirections(t_tree **head, t_list *node, t_list *next_node);

/* heredoc */

/* heredoc utils */
char	**split_dollar_hd(const char *line);


/* command */
void	execve_command(t_data *data);
int	is_builtin(char *str);
void	execve_builtin(t_data *data);
int	do_command(t_data *data, t_tree *tree);

/* add test code */
int	test_code(t_list **node);
t_tree	*make_tree(t_list **node);
/* add test code */


int	do_fork(t_data *data);

/* init */
void	init_data(int argc, char **argv, char **envp, t_data *data);

/* built-in */
// int		echo_command(t_data *data);
void	cd_command(t_data *data);
void	pwd_command(t_data *data);
void	exit_command(t_data *data);
void	env_command(t_data *data);
void	export_command(t_data *data);
void	unset_command(t_data *data);
void	echo_command(char **array);

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
// int	here_doc(t_data *data, t_tree *tree);
int	preprocess_heredoc(t_data *data, t_tree *tree);

/* signals */
void	set_signals(void);

/* utils0 */
int		is_equal_to(char *str1, char *str2);
void	print_all_arguments(int argc, char **argv, char **envp);
void	print_all_argument_value(char **argv);
void	free_double_array(char **array);
void	exit_with_str(const char *str, int exit_code);
int		ft_open(const char *path, int oflag, int flag);
void	ft_close(int fd);
int		ft_dup(int old_fd);
void	ft_dup2(int old_fd, int new_fd);
// void	ft_fork(pid_t *pid);
void	ft_unlink(const char *path);
void	ft_wait(int *wstatus);
// int	do_wait(t_data *data);
// int	do_wait_bonus(t_data *data);
// void	ft_chdir(const char *path, const char *cmd);
char	*ft_strjoin_wslash(char *str1, char *str2);
// char	*find_command_path(t_data *data);
char	**copy_double_array(char **origin_array);
size_t	strlen_before_equal(char *str);
int		get_size_double_array(char **array);
void	print_double_array(char **array);
int		ft_getenv(char **array, char *str);

/* envp_utils */
char	**add_environment_variable(char **array, char *key);
char	**delete_environment_variable(char **array, char *key);

#endif
