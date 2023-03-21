/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:42:40 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/20 18:34:11 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

int	check_type(const char *str)
{
	if (*str == '|')
		return (PIPE);
	if (*str == '<' || *str == '>')
	{
		if (!ft_strncmp(str, "<<<", 3) || !ft_strncmp(str, ">>>", 3))
			return (ZERO);
		return (REDIR_TOKEN);
	}
	return (WORD);
}

char	*remove_quote(const char *line)
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

void	get_token(const char *line, size_t size, t_list **list, t_data *data)
{
	t_list	*node;
	char	*expansion;
	char	*content;
	int		type;

	expansion = expand_str(line, size, data);
	type = check_type(expansion);
	content = remove_quote(expansion);
	free(expansion);
	node = create_element(type, content);
	lst_addback(list, node);
}
