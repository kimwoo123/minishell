/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 22:00:37 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:59:29 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line_bonus.h"

char	*seperate_str(t_fdlist *node)
{
	size_t	index;
	char	*line;
	char	*free_strg;

	index = 0;
	while (node->strg[index] && node->strg[index] != '\n')
		index++;
	if (!node->strg[index] && !index)
		return (0);
	free_strg = node->strg;
	line = ft_substr(node->strg, 0, index + 1);
	node->strg = ft_substr(node->strg, index + 1, ft_strlen(node->strg));
	free(free_strg);
	return (line);
}

int	read_file(int fd, t_fdlist *node)
{
	char	*buf;
	char	*temp;
	ssize_t	read_size;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	read_size = 1;
	while (ft_strchr(node->strg, '\n') == -1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		buf[read_size] = '\0';
		temp = node->strg;
		node->strg = ft_strjoin(temp, buf);
		free(temp);
	}
	free(buf);
	if (read_size < 0)
		return (0);
	return (1);
}

t_fdlist	*ft_lstnew(t_fdlist *prev_node, int fd)
{
	t_fdlist	*result;

	result = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!result)
		return (0);
	result->fd = fd;
	result->strg = (char *)malloc(1);
	if (!result->strg)
	{
		free(result);
		return (0);
	}
	result->strg[0] = '\0';
	result->prev = prev_node;
	result->next = 0;
	return (result);
}

t_fdlist	*find_node(t_fdlist *node, int fd)
{
	t_fdlist	*temp;

	while (node)
	{
		if (node->fd == fd)
			return (node);
		temp = node;
		node = node->next;
	}	
	node = ft_lstnew(temp, fd);
	if (!node)
		return (0);
	temp->next = node;
	return (node);
}

char	*get_next_line(int fd)
{
	static t_fdlist		*head;
	t_fdlist			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!head)
		head = ft_lstnew(0, fd);
	node = find_node(head, fd);
	if (!node)
		return (0);
	if (!read_file(fd, node))
	{
		free_node(&head, node);
		return (0);
	}
	line = seperate_str(node);
	if (!(line))
	{
		free_node(&head, node);
		return (0);
	}
	return (line);
}
