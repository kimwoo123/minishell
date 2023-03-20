/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:14:25 by chajung           #+#    #+#             */
/*   Updated: 2023/03/13 13:14:26 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redir(char **argv)
{
	int	fd;

	if (is_equal_to("<", argv[0]) == NOT_SAME)
		return (FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == FAILURE)
		return (FAILURE);
	if (dup2(fd, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	output_redir(char **argv)
{
	int	fd;

	if (is_equal_to(">", argv[0]) == NOT_SAME)
		return (FAILURE);
	fd = open(argv[1], (O_WRONLY | O_CREAT | O_TRUNC), 0644);
	if (fd == FAILURE)
		return (FAILURE);
	if (dup2(fd, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	output_append_redir(char **argv)
{
	int	fd;

	if (is_equal_to(">>", argv[0]) == NOT_SAME)
		return (FAILURE);
	fd = open(argv[1], (O_WRONLY | O_CREAT | O_APPEND), 0644);
	if (fd == FAILURE)
		return (FAILURE);
	if (dup2(fd, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

char	*join_redirection(t_tree *tree)
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

int	do_redirection(t_data *data, t_tree *tree)
{
	char	*temp;

	temp = join_redirection(tree);
	if (temp == NULL)
		return (FAILURE);
	data->commands = ft_split(temp, ' ');
	if (data->commands == NULL)
		return (FAILURE);
	free(temp);

	// data->commands = join_redirection(tree);
	// if (data->commands == NULL)
	// 	return (FAILURE);
	
	// write(2, "TEST\n", 5);
	if (is_equal_to(data->commands[0], "<") == SAME)
		input_redir(data->commands);
	else if (is_equal_to(data->commands[0], ">") == SAME)
		output_redir(data->commands);
	else if (is_equal_to(data->commands[0], ">>") == SAME)
		output_append_redir(data->commands);
	else if (is_equal_to(data->commands[0], "<<") == SAME)
		here_doc(data);
	return (SUCCESS);
}
