/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:38:00 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/22 10:47:34 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# define DELIMITER			"<>|"
# define DOLLAR				'$'
# define SIGINT				2
# define SIGQUIT			3
# define EXIT_SUCCESS		0
# define EXIT_FAILURE		1
# define COMMAND_NOT_FOUND	127
# define SUCCESS			0
# define FAILURE			-1
# define CHILD_PROCESS  	0
# define ONLY_KEY			1
# define KEY_AND_VALUE		2

typedef struct s_stack
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
	pid_t	pid;
	int		redir_in;
	int		redir_out;
	int		count_pipe;
	int		redir_stat;
	int		hd_flag;
	int		has_forked;
	int		last_cmd;
	int		pipe_fd[2];
	int		dup_stdin;
	int		dup_stdout;
}	t_data;

typedef struct s_list
{
	int				type;
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_tree
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

enum e_bool
{
	FALSE,
	TRUE,
};

#endif
