/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deli_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:45:52 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/14 09:16:55 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static size_t	trim_line(const char *line)
{
	size_t	index;

	index = 0;
	while (line[index] && is_space(line[index]))
		index++;
	return (index);
}

static int	is_delimiter(const char c)
{
	int	index;

	index = 0;
	while (DELIMITER[index])
	{
		if (DELIMITER[index] == c)
			return (1);
		index++;
	}
	return (0);
}

int	is_quote(const char c)
{
	return (c == '\'' || c == '\"');
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while ((s1[index] || s2[index]) && index < n)
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

char *ft_strndup(const char *begin, size_t size)
{
	size_t	index;
	char	*result;

	result = (char *)malloc(size + 1);
	if (!result)
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

char	check_quote(const char c, char flag)
{
	if (flag && flag == c)
		return ('\0');
	else if (!flag && is_quote(c))
		return (c);
	return (flag);
}

void	seperate_meta(const char *line, size_t size, t_list **node)
{
	size_t	index;
	size_t	start_index;

	index = trim_line(&line[0]);
	start_index = index;
	if (is_delimiter(line[index]))
	{
		while (index < size && is_delimiter(line[index]))
			index++;
		get_token(&line[start_index], index - start_index, node);
		if (size != index)
			get_token(&line[index], size - index, node);
	}
	else
		get_token(&line[index], size - index, node);
}

// space 기준으로 분리
void	split_space(const char *line, size_t size, t_list **node)
{
	size_t	index;
	size_t	start_index;
	int		space_flag;
	char	quote_flag;

	start_index = 0;
	space_flag = 0;
	quote_flag = '\0';
	index = -1;
	while (++index < size)
	{
		quote_flag = check_quote(line[index], quote_flag);
		if (!quote_flag && (space_flag && is_space(line[index])))
		{
			seperate_meta(&line[start_index], index - start_index, node);
			start_index = index;
			space_flag = 0;
		}
		else if (!quote_flag && (!space_flag && !is_space(line[index])))
			space_flag = 1;
	}
	if (space_flag)
		seperate_meta(&line[start_index], index - start_index, node);
}

int	repeat_meta(const char *line, size_t index)
{
	if (index > 0)
		if (!ft_strncmp(&line[index - 1], "<<" , 2) || !ft_strncmp(&line[index - 1], ">>", 2))
			return (1);
	return (0);
}

// return (0)일 경우 따옴표가 닫히지 않은 상태
// DELIMITER MACRO 기준으로 분리
void	split_delimiter(const char *line, t_list **node)
{
	size_t	index;
	size_t	start_index;
	char	quote_flag;

	quote_flag = '\0';
	start_index = 0;
	index = -1;
	while (line[++index])
	{
		quote_flag = check_quote(line[index], quote_flag);
		if ((!quote_flag && is_delimiter(line[index])) && !repeat_meta(line, index))
		{
			split_space(&line[start_index], index - start_index, node);
			start_index = index;
		}
	}
	split_space(&line[start_index], index - start_index, node);
}

size_t	count_meta_repeat(char const *line)
{
	size_t	index;
	size_t	count;

	count = 0;
	index = 0;
	while (line[index] == *line)
	{
		++index;
		++count;
	}
	return (count);
}

int	close_quote(const char *line)
{
	char	quote_flag;
	size_t	index;

	quote_flag = '\0';
	index = 0;
	while (line[index])
	{
		quote_flag = check_quote(line[index], quote_flag);
		if (quote_flag != '\'' && is_delimiter(line[index]))
			count_meta_repeat(&line[index]);
		++index;
	}
	if (quote_flag != '\0')
		return (0);
	return (1);
}

void	scan_command(const char *line)
{
	t_list *list;

	if (close_quote(line) == 0)
	{
		printf("quote error");
		exit(1);
	}
	list = NULL;
	split_delimiter(line, &list);
	search_list(list);
}

void	search_tree(t_node *node)
{
	t_node *temp;

	temp = node;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->left_child;
	}
}

void	search_list(t_list *list)
{
	t_list *temp;

	temp = list;
	while (temp)
	{
		printf("%s, %d\n", temp->content, temp->type);
		temp = temp->next;
	}
}
