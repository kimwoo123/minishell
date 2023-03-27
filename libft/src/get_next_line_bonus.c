/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:35:32 by chajung           #+#    #+#             */
/*   Updated: 2022/11/24 20:35:40 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static t_node	*too_many_lines(t_node **head, int fd)
{
	t_node	*node;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!(*head))
	{
		*head = (t_node *)malloc(sizeof(t_node));
		if (!(*head))
			return (NULL);
		(*head)->fd = -2;
		(*head)->next = NULL;
		(*head)->backup = NULL;
	}
	node = find_node(head, fd);
	if (!node)
		return (NULL);
	if (!node->backup)
	{
		node->backup = (char *)malloc(sizeof(char));
		if (!node->backup)
			return (NULL);
		node->backup[0] = '\0';
	}
	return (node);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	char			*line;

	node = too_many_lines(&head, fd);
	if (!node)
		return (NULL);
	line = read_line(node->backup, fd);
	if (!line)
	{
		clear_node(&head, node);
		return (NULL);
	}
	node->backup = clean_up(line);
	if (!(*line) && !(node->backup))
	{
		free(line);
		clear_node(&head, node);
		return (NULL);
	}
	return (line);
}
