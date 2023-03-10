/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:24:20 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/12 18:44:43 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*create_element(int type, char *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	elem->type = type;
	elem->content = content;
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

int		check_type(const char *str)
{
	if (*str == '|')
		return (PIPE);
	if (*str == '<' || *str == '>')
		return (REDIRECTION);
	return (WORD);
}

size_t	ft_strlen(char const *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*addr;

	addr = (char *)malloc(sizeof(char) \
		* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (addr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		addr[i++] = *s1++;
	while (*s2)
		addr[i++] = *s2++;
	addr[i] = '\0';
	return (addr);
}

void	get_token(char const *line, size_t size, t_list **list)
{
	t_list	*node;
	char	*content;
	int		type;

	content = convert_dollar(line, size);
	type = check_type(content);
	node = create_element(type, content);
	lst_addback(list, node);
}
