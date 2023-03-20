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

	dprintf(2, "TEST\n");
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

int	split_redirection(t_data *data, t_tree *tree)
{
	char	*temp;

	temp = join_redirection(tree);
	if (temp == NULL)
		return (FAILURE);
	data->commands = ft_split(temp, ' ');
	if (data->commands == NULL)
		return (FAILURE);
	free(temp);
	return (SUCCESS);
}

int	input_redir_hd(t_data *data, t_tree *tree)
{
	int	fd;

	fd = ft_open("heredoc_temp", (O_WRONLY | O_CREAT | O_TRUNC), 0644);
	if (fd == FAILURE)
		return (FAILURE);
	write(fd, tree->right->content, ft_strlen(tree->right->content));
	close(fd);
	fd = open("heredoc_temp", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	ft_unlink("heredoc_temp");
	return (SUCCESS);
}

int	do_redirection(t_data *data, t_tree *tree)
{
	if (split_redirection(data, tree) == FAILURE)
		return (FAILURE);
	if (is_equal_to(data->commands[0], "<") == SAME)
		input_redir(data->commands);
	else if (is_equal_to(data->commands[0], "<<") == SAME)
		input_redir_hd(data, tree);
	else if (is_equal_to(data->commands[0], ">") == SAME)
		output_redir(data->commands);
	else if (is_equal_to(data->commands[0], ">>") == SAME)
		output_append_redir(data->commands);
	return (SUCCESS);
}
