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

#include "minishell_bonus.h"

static int	input_redir(t_data *data)
{
	int	fd;

	if (is_equal_to("<", data->commands[0]) == FALSE)
		return (FAILURE);
	fd = open(data->commands[1], O_RDONLY);
	if (fd == FAILURE)
	{
		ft_putstr_fd(data->commands[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		data->redir_stat = TRUE;
		set_status(EXIT_FAILURE);
		return (SUCCESS);
	}
	if (dup2(fd, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(fd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	input_redir_hd(t_tree *tree)
{
	int	fd;

	fd = open("heredoc_temp", (O_WRONLY | O_CREAT | O_TRUNC), 0644);
	if (fd == FAILURE)
		return (FAILURE);
	write(fd, tree->right->content, ft_strlen(tree->right->content));
	close(fd);
	fd = open("heredoc_temp", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (unlink("heredoc_temp") == FAILURE)
		return (FAILURE);
	if (close(fd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	output_redir(char **argv)
{
	int	fd;

	if (is_equal_to(">", argv[0]) == FALSE)
		return (FAILURE);
	fd = open(argv[1], (O_WRONLY | O_CREAT | O_TRUNC), 0644);
	if (fd == FAILURE)
		return (FAILURE);
	if (dup2(fd, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(fd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	output_append_redir(char **argv)
{
	int	fd;

	if (is_equal_to(">>", argv[0]) == FALSE)
		return (FAILURE);
	fd = open(argv[1], (O_WRONLY | O_CREAT | O_APPEND), 0644);
	if (fd == FAILURE)
		return (FAILURE);
	if (dup2(fd, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(fd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	do_redirection(t_data *data, t_tree *tree)
{
	int	result;

	result = SUCCESS;
	if (split_redirection(data, tree) == FAILURE)
		exit_with_str("malloc error in do redirection", EXIT_FAILURE);
	if (is_equal_to(data->commands[0], "<") == TRUE)
		result = input_redir(data);
	else if (is_equal_to(data->commands[0], "<<") == TRUE)
		result = input_redir_hd(tree);
	else if (is_equal_to(data->commands[0], ">") == TRUE)
	{
		result = output_redir(data->commands);
		data->redir_out = TRUE;
	}
	else if (is_equal_to(data->commands[0], ">>") == TRUE)
	{
		result = output_append_redir(data->commands);
		data->redir_out = TRUE;
	}
	if (result == FAILURE)
		exit_with_str("error in do redirection", EXIT_FAILURE);
}
