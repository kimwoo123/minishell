/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:10 by chajung           #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/03/01 17:21:11 by chajung          ###   ########.fr       */
=======
/*   Updated: 2023/03/20 19:43:54 by wooseoki         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************************************/
// char	*join_redirection(t_tree *tree)
// {
// 	char	*temp;
// 	char	*new_str;

// 	temp = ft_strjoin(tree->left->content, " ");
// 	if (temp == NULL)
// 		return (NULL);
// 	new_str = ft_strjoin(temp, tree->right->content);
// 	if (new_str == NULL)
// 		return (NULL);
// 	free(temp);
// 	return (new_str);
// }

char	*ft_strjoin_wspace(char *str1, char *str2)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(str1, " ");
	if (temp == NULL)
		return (NULL);
	new_str = ft_strjoin(temp, str2);
	if (new_str == NULL)
		return (NULL);
	free(temp);
	return (new_str);
}

char	*join_command(t_tree *tree)
{
	char	*str;
	char	*new_str;
	t_tree	*temp;

	str = ft_strdup(tree->left->content);
	if (str == NULL)
		return (NULL);
	temp = tree->right;
	while (temp != NULL)
	{
		if (temp->left != NULL)
		{
			new_str = ft_strjoin_wspace(str, temp->left->content);
			if (new_str == NULL)
				return (NULL);
			free(str);
			str = new_str;
			new_str = NULL;
		}
		temp = temp->right;
	}
	return (str);
}
/************************************************************/

int	execve_builtin(t_data *data)
{
	int	result;

	result = FAILURE;
	if (is_equal_to(data->commands[0], "echo") == SAME)
		result = echo_command(data->commands);
	else if (is_equal_to(data->commands[0], "cd") == SAME)
		result = cd_command(data);
	else if (is_equal_to(data->commands[0], "pwd") == SAME)
		result = pwd_command(data);
	else if (is_equal_to(data->commands[0], "export") == SAME)
		result = export_command(data);
	else if (is_equal_to(data->commands[0], "unset") == SAME)
		result = unset_command(data);
	else if (is_equal_to(data->commands[0], "env") == SAME)
		result = env_command(data);
	else if (is_equal_to(data->commands[0], "exit") == SAME)
		result = exit_command(data);
	return (result);
}

int	is_builtin(char *str)
{
	if (is_equal_to(str, "echo") == SAME \
	|| is_equal_to(str, "cd") == SAME \
	|| is_equal_to(str, "pwd") == SAME \
	|| is_equal_to(str, "export") == SAME \
	|| is_equal_to(str, "unset") == SAME \
	|| is_equal_to(str, "env") == SAME \
	|| is_equal_to(str, "exit") == SAME)
		return (FOUND);
	return (NOT_FOUND);
}

int	execve_command(t_data *data)
{
	char	*command_path;

	command_path = find_command_path(data);
	if (command_path == NULL)
	{
		printf("%s: command not found\n", data->commands[0]);
		return (1);
	}
	else
	{
		if (execve(command_path, data->commands, data->envp) == FAILURE)
			ft_perror("execve error", EXIT_FAILURE);
		return (1);
	}
	return (0);
}

int	is_not_builtin(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILURE)
		ft_perror("fork error", EXIT_FAILURE);
	if (pid == CHILD_PROCESS)
	{
		if (data->last_cmd != TRUE)
		{
			ft_close(data->pipe_fd[STDIN_FILENO]);
			ft_dup2(data->pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
			ft_close(data->pipe_fd[STDOUT_FILENO]);
		}
		if (is_builtin(data->commands[0]) == TRUE)
			execve_builtin(data);
		else
			execve_command(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (data->last_cmd != TRUE)
		{
			ft_close(data->pipe_fd[STDOUT_FILENO]);
			ft_dup2(data->pipe_fd[STDIN_FILENO], STDIN_FILENO);
			ft_close(data->pipe_fd[STDIN_FILENO]);
			wait(0);
		}
		else
			waitpid(pid, &data->stat, 0);
	}
	return (0);
}

static int	do_pipe(t_data *data, t_tree *tree)
{
	if (tree->right == NULL)
		data->last_cmd = TRUE;
	else if (tree->right != NULL)
	{
		data->has_forked = TRUE;
		if (pipe(data->pipe_fd) == FAILURE)
			return (FAILURE);
			// ft_perror("pipe error in pipe", EXIT_FAILURE);
	}
	return (SUCCESS);
}

static int	do_command(t_data *data, t_tree *tree)
{
	char	*temp;
	
	temp = join_command(tree);
	if (temp == NULL)
		return (FAILURE);
	data->commands = ft_split(temp, ' ');
	if (data->commands == NULL)
		return (FAILURE);
	free(temp);
	if (data->has_forked == FALSE && is_builtin(data->commands[0]) == TRUE)
		execve_builtin(data);
	else
		is_not_builtin(data);
	return (SUCCESS);
}

int	execve_command_line(t_data *data, t_tree *tree)
{
	if (tree->type == PIPE)
		do_pipe(data, tree);
	else if (tree->type == REDIRECTION)
		do_redirection(data, tree);
	else if (tree->type == PARENT_CMD && tree->left != NULL)
		do_command(data, tree);
	return (0);
}

static void	search_tree(t_data *data, t_tree *head)
{
	if (head == NULL)
		return ;
	if (head->type == PIPE \
	|| head->type == REDIRECTION \
	|| head->type == PARENT_CMD)
		execve_command_line(data, head);
	if (head->left != NULL)
		search_tree(data, head->left);
	if (head->right != NULL)
		search_tree(data, head->right);
}

void	make_nice_name(t_data *data, char *command_line)
{
	t_list	*list;
	t_tree	*tree;

	data->last_cmd = FALSE;
	data->has_forked = FALSE;
	data->dup_stdin = ft_dup(STDIN_FILENO);
	data->dup_stdout = ft_dup(STDOUT_FILENO);
	list = scan_command(command_line);
	if (list == NULL)
		rl_on_new_line();
	else
	{
		tree = make_tree(&list);
		search_tree(data, tree);
		// free(list);
		// free(tree);
	}
	ft_dup2(data->dup_stdin, STDIN_FILENO);
	ft_dup2(data->dup_stdout, STDOUT_FILENO);
	ft_close(data->dup_stdin);
	ft_close(data->dup_stdout);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*command_line;

	init_data(argc, argv, envp, &data);
	set_signals();
	while (1)
	{
		command_line = readline("minishell> ");
		if (command_line == NULL)
			break ;
		add_history(command_line);
		make_nice_name(&data, command_line);
		free (command_line);
		system("leaks --list -- $PPID");
	}
	ft_putendl_fd("bye", STDOUT_FILENO);
	return (0);
}
