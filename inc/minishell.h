/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:46 by chajung           #+#    #+#             */
/*   Updated: 2023/03/18 17:05:11 by wooseoki         ###   ########.fr       */
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

# include "../libft/inc/libft.h"

# define SIGINT			2
# define SIGQUIT		3

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

# define SUCCESS		0
# define FAILURE		-1

# define CHILD_PROCESS  0

# define NOT_FOUND		0
# define ONLY_KEY		1
# define KEY_AND_VALUE	2

# define NOT_FOUND		0
# define FOUND			1

# define NOT_SAME		0
# define SAME			1


# define DELIMITER	"<>|"
# define DOLLAR		'$'

typedef	struct	s_stack
{
	int				type;
	char			*content;
	struct s_stack	*next;
}	t_stack;

typedef int	(*t_fptr)(t_stack **stack_node);


typedef struct s_data
{
	char	**envp;
	char	**copied_envp;
	char	**commands;
	int		hd_flag;
	int		has_forked;
	int		stat;
	int		last_cmd;
	int		pipe_fd[2];
	int		dup_stdin;
	int		dup_stdout;
}	t_data;

typedef struct	s_list
{
	int				type;
	char			*content;
	struct s_list	*next;
}	t_list;

typedef	struct	s_tree
{
	int				type;
	char			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

enum	e_type
{
	ZERO,
	WORD,
	REDIR_TOKEN,
	REDIRECTION,
	CMD_TOKEN,
	COMMAND,
	PIPE_CMD,
	PARENT_REDIR,
	PARENT_CMD,
	GROUP_CMD,
	QUOTE,
	PIPE
};

enum	e_bool
{
	FALSE,
	TRUE,
}	t_bool;

char	*ft_getenv(char **array, char *str);

char 	*ft_strndup(const char *begin, size_t size);

void	search_tree_for_hd(t_data *data, t_tree *head);
void	search_tree(t_data *data, t_tree *head);

void	run_minishell(t_data *data, char *command_line);

void	exit_with_str(const char *str, int exit_code);

void	free_tree(t_tree *node);

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
int		is_there_envp(char **array, char *str);

/* envp_utils */
char	**add_environment_variable(char **array, char *key);
char	**delete_environment_variable(char **array, char *key);


/**/


/* lexer */
void	seperate_meta(const char *line, size_t size, t_list **list, t_data *data);
void	split_space(const char *line, size_t size, t_list **list, t_data *data);
int		repeat_meta(const char *line, size_t index);
void	split_delimiter(const char *line, t_list **list, t_data *data);
t_list	*scan_command(const char *line, t_data *data);
 
/* parse_utils */
char	check_quote(char c, char flag);
int		is_delimiter(char c);
size_t	trim_line(const char *line);
int		close_quote(const char *line);

/* utils */
char 	*ft_strndup(const char *begin, size_t size);
int		is_space(char c);
int		is_quote(char c);

/* token */
t_list	*create_element(int type, char *content);
void	get_token(const char *line, size_t size, t_list **token_list, t_data *data);
int		check_type(const char *str);
void	lst_addback(t_list **list, t_list *node);
char	*remove_quote(const char *line);

/* split_dollar */
size_t	get_dollar_len(const char *line);
size_t	get_dollar_index(const char *line, char *quote_flag);
size_t	double_array_size(const char *line, char *quote_flag);
void	duplicate_str(char **result, const char *line, char *quote_flag);
char	**split_dollar(const char *line, size_t size);

/* expand_str */
char	*convert_variable(char *str, t_data *data);
char	*merge_str(char **split_str);
char	*expand_str(const char *line, size_t size, t_data *data);
char	*convert_dollar(char **str, t_data *data);

/* free */
void	free_list(t_list **list);
void	free_double(char **str);
void	free_stack_table(t_stack *stack, t_fptr **table);

/* syntax */
int	check_syntax(t_list **token_list);
int	repeat_reduce_shift(t_fptr **reduce_table, t_stack **stack);
int	reduce_token(t_fptr **reduce_table, t_stack **stack_node);
int	shift_token(t_fptr **reduce_table, t_stack **stack_node);
int	parse_token(t_list **token_list);

/* stack */
t_stack	*create_elem(int type);
int	pop_stack(t_stack **stack);
void	push_stack(t_stack **stack, int	type);

/* reduce_rule */
int	reduce_redirection(t_stack **stack_node);
int	reduce_cmd_token(t_stack **stack_node);
int	reduce_command(t_stack **stack_node);
int	reduce_pipe_command(t_stack **stack_node);
int	reduce_group_command(t_stack **stack_node);

/* shift_rule */
int	shift_command(t_stack **stack_node);
int	shift_r_command(t_stack **stack_node);
int	shift_ct_command(t_stack **stack_node);
int	shift_w_ct(t_stack **stack_node);

/* set_table */
void	set_reduce_function(t_fptr **reduce_table);
t_fptr **init_parse_table(void);
/**/


#endif
