/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:07:58 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:59:37 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line_bonus.h"

int	ft_strchr(char *str, int c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == (char)c)
			return (index);
		index++;
	}
	if (str[index] == (char)c)
		return (index);
	return (-1);
}

char	*ft_substr(char *str, size_t start, size_t len)
{
	size_t			index;
	size_t			str_len;
	char			*substr;

	str_len = ft_strlen(str);
	if (str_len <= start)
		return (ft_strjoin("", ""));
	if (str_len - start < len)
		len = str_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (0);
	index = 0;
	while (str[start + index] && index < len)
	{
		substr[index] = str[start + index];
		index++;
	}
	substr[index] = '\0';
	return (substr);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*result;
	char	*temp;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(total_len + 1);
	if (!result)
		return (0);
	temp = result;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (result);
}

void	free_node(t_fdlist **head, t_fdlist *node)
{
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->strg);
	node->strg = NULL;
	free(node);
	node = NULL;
}
