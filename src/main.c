/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:10 by chajung           #+#    #+#             */
/*   Updated: 2023/03/01 17:21:11 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************************************/
char	*redirection_join(t_tree *tree)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(tree->left->content, " ");
	if (temp == NULL)
		return (NULL);
	new_str = ft_strjoin(temp, tree->right->content);
	if (new_str == NULL)
		return (NULL);
	free(temp);
	return (new_str);
}

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

char	*command_join(t_tree *tree)
{
	char	*str;
	char	*new_str;
	t_tree	*temp;

	str = tree->left->content;
	temp = tree->right;
	while (temp != NULL)
	{
		if (temp->left != NULL)
		{
			new_str = ft_strjoin_wspace(str, temp->left->content);
			free(str);
			str = new_str;
			new_str = NULL;
		}
		temp = temp->right;
	}
	return (str);
}
/************************************************************/

int	execute_command(t_data *data)
{
	char	*command_path;

	command_path = find_command_path(data);
	if (command_path == NULL)
	{
		// perror(data->commands[0]);
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

int	exec_builtin(t_data *data)
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

int	is_not_builtin(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILURE)
		ft_perror("fork error", EXIT_FAILURE);
	if (pid == CHILD_PROCESS)
	{
		execute_command(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_wait(NULL);
	}
	return (0);
}

int	parsing_command_line(t_data *data)
{
	if (data->commands[0] == NULL)
		rl_on_new_line();
	else if (is_equal_to(data->commands[0], "<<") == SAME)
		here_doc(data);
	else if (is_equal_to(data->commands[0], "|") == SAME)
		return (0); // PIPE
	else if (is_builtin(data->commands[0]) == FOUND)
		exec_builtin(data);
	else
		is_not_builtin(data);
	return (0);
}

int	execve_command_line(t_data *data, t_tree *tree)
{
	char	*temp;

	// printf("%d: %s\n", tree->type, tree->content);
	if (tree->type == PIPE)
	{
		if (tree->right == NULL) // DO NOT PIPE !
			return (0);
		else if (tree->right != NULL) // DO PIPE!
			return (0);
	}
	else if (tree->type == REDIRECTION)
	{
		return (0);
	}
	else if (tree->type == PARENT_CMD && tree->left != NULL)
	{
		// printf("command: %s\n", command_join(tree));
		temp = command_join(tree);
		data->commands = ft_split(temp, ' ');
		free(temp);
		if (is_builtin(data->commands[0]) == FOUND)
			exec_builtin(data);
		else
			is_not_builtin(data);
		// return (0);
	}
	return (0);
}

static void	test_search_tree(t_data *data, t_tree *head)
{
	if (head == NULL)
		return ;
	if (head->type == PIPE || head->type == REDIRECTION \
	|| head->type == PARENT_CMD)
		execve_command_line(data, head);
	if (head->left != NULL)
		test_search_tree(data, head->left);
	if (head->right != NULL)
		test_search_tree(data, head->right);
}

void	make_nice_name(t_data *data, char *command_line)
{
	t_list	*list;
	t_tree	*tree;

	list = scan_command(command_line);
	if (list == NULL)
		rl_on_new_line();
	tree = make_tree(&list);
	test_search_tree(data, tree);
	free(list);
	free(tree);
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
	}
	return (0);
}
