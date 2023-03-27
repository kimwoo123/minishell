/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:35:51 by chajung           #+#    #+#             */
/*   Updated: 2022/11/30 16:30:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	clear_node(t_node **head, t_node *node)
{
	t_node	*temp;
	t_node	*prev_node;
	int		list_size;

	list_size = 0;
	temp = (*head);
	while (temp->next)
	{
		if (temp->next == node)
			prev_node = temp;
		temp = temp->next;
		list_size++;
	}
	prev_node->next = node->next;
	free(node->backup);
	free(node);
	if (list_size == 1)
	{
		free(*head);
		*head = NULL;
	}
}

t_node	*find_node(t_node **head, int fd)
{
	t_node	*new_node;
	t_node	*temp;

	temp = (*head);
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		if (!(temp->next))
			break ;
		temp = temp->next;
	}
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->backup = NULL;
	new_node->next = NULL;
	temp->next = new_node;
	return (new_node);
}

char	*clean_up(char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (NULL);
	temp = ft_substr(line, i + 1, ft_strlen(line));
	if (!temp)
		return (NULL);
	line[i + 1] = '\0';
	return (temp);
}

char	*read_line(char *backup, int fd)
{
	int		read_byte;
	char	*temp;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_byte = 0;
	while (!ft_strchr(backup, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte <= 0)
			break ;
		buffer[read_byte] = '\0';
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		if (!backup)
			break ;
		free(temp);
	}
	free(buffer);
	if (read_byte < 0)
		return (NULL);
	return (backup);
}
