/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:44:33 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/28 10:46:33 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*ft_strndup(const char *begin, size_t size)
{
	size_t	index;
	char	*result;

	result = (char *)malloc(size + 1);
	if (result == NULL)
		return (NULL);
	index = 0;
	while (index < size)
	{
		result[index] = begin[index];
		++index;
	}
	result[index] = '\0';
	return (result);
}

t_list	*create_element(int type, char *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	elem->type = type;
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

void	lst_addback(t_list **list, t_list *node)
{
	t_list	*temp;

	if (!(*list))
	{
		*list = node;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}
