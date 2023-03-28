/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:46 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 18:47:18 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "parse_bonus.h"
# include "structure_bonus.h"
# include "../libft/inc/libft.h"

/* built-in */
void	cd_command(t_data *data);
void	pwd_command(void);
void	exit_command(t_data *data);
void	env_command(t_data *data);
void	export_command(t_data *data);
void	unset_command(t_data *data);
void	echo_command(char **array);

/* cd utils0 */
int		change_dir_nothing(t_data *data);
int		change_dir_to_home(t_data *data);
int		change_dir_to_root(char **commands);
int		change_dir(char **commands);

/* cd utils1 */
int		backup_working_directory(t_data *data);
int		change_working_directory(t_data *data);

/* cd utils2 */
void	ft_chdir(const char *path, const char *cmd);
char	*find_home_path(char **envp);

/* export utils0 */
void	print_not_vaild_identifier(char *str);
void	sort_double_array(char **array);
int		check_equal_sign(char *str);
void	print_with_double_quotation(char *str);

/* export utils1 */
int		copy_additional_args(t_data *data, char **array, size_t *array_index);
int		copy_origin_arguments(t_data *data, char **array, size_t *index);
char	**alloc_double_array(t_data *data);

/* init */
void	init_data(int argc, char **argv, char **envp, t_data *data);

/* signal */
void	set_signals(void);

/* run */
void	run_minishell(t_data *data, char *command_line);

/* tree */
void	search_tree(t_data *data, t_tree *head);
void	search_tree_for_hd(t_data *data, t_tree *head);

/* tree utils0 */
t_tree	*make_tree(t_list **node);
t_tree	*create_root(void);
t_tree	*create_tree(int type, char *content, t_tree *left, t_tree *right);

/* tree utils1 */
void	add_commands(t_tree **head, t_list *node);
void	add_redirections(t_tree **head, t_list *node, t_list *next_node);
void	add_pipe(t_tree **head);

/* redir */
void	do_redirection(t_data *data, t_tree *tree);

/* redir utils */
int		split_redirection(t_data *data, t_tree *tree);
char	*join_redirection(t_tree *tree);

/* heredoc */
int		preprocess_heredoc(t_data *data, t_tree *tree);

/* heredoc utils */
char	**split_dollar_hd(const char *line);

/* command */
void	execve_command(t_data *data);

/* command utils */
int		do_command(t_data *data, t_tree *tree);
int		is_builtin(char *str);
void	execve_builtin(t_data *data);

/* fork */
void	do_fork(t_data *data);

/* envp utils */
char	*ft_getenv(char **array, char *str);
int		is_there_envp(char **array, char *str);
char	**delete_environment_variable(char **array, char *key);
char	**add_environment_variable(char **array, char *key);

/* utils0 */
int		is_equal_to(char *str1, char *str2);
size_t	strlen_before_equal(char *str);
size_t	get_size_double_array(char **array);
char	*ft_strjoin_wslash(char *str1, char *str2);
char	**copy_double_array(char **origin_array);

/* utils1 */
void	exit_with_str(const char *str, int exit_code);
void	set_status(int stat);

#endif
