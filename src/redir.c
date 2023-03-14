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

