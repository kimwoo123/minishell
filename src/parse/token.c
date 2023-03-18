/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:42:40 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 15:52:21 by wooseoki         ###   ########.fr       */
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

int		check_type(const char *str)
{
	if (*str == '|')
		return (PIPE);
	if (*str == '<' || *str == '>')
		return (REDIR_TOKEN);
	return (WORD);
}
/*
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
*/
char	*remove_quote(char const *line)
{
	char	quote_flag;
	char	*result;
	size_t	index;
	size_t	r_index;

	result = (char *)malloc(ft_strlen(line) + 1);
	if (result == NULL)
		return (NULL);
	quote_flag = '\0';
	index = 0;
	r_index = 0;
	while (line[index])
	{
		if (!quote_flag && is_quote(line[index]))
			quote_flag = line[index];
		else if (quote_flag == line[index])
			quote_flag = '\0';
		else
			result[r_index++] = line[index];
		++index;
	}
	result[r_index] = '\0';
	return (result);
}

void	get_token(char const *line, size_t size, t_list **list)
{
	t_list	*node;
	char	*expansion;
	char	*content;
	int		type;

	expansion = expand_str(line, size);
	type = check_type(expansion);
	content = remove_quote(expansion);
	node = create_element(type, content);
	lst_addback(list, node);
}
