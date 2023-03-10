/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deli_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:45:52 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/10 09:57:50 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static int	is_space(const char c)
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
		index++;
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
}

void	seperate_meta(const char *line, size_t size, t_list **list)
{
	size_t	index;
	size_t	start_index;

	index = trim_line(&line[0]);
	start_index = index;
	if (is_delimiter(line[index]))
	{
		while (index < size && is_delimiter(line[index]))
			index++;
		get_token(&line[start_index], index - start_index, list);
		if (size != index)
			get_token(&line[index], size - index, list);
	}
	else
		get_token(&line[index], size - index, list);
}

// space 기준으로 분리
void	split_space(const char *line, size_t size, t_list **list)
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
			seperate_meta(&line[start_index], index - start_index, list);
			start_index = index;
			space_flag = 0;
		}
		else if (!quote_flag && (!space_flag && !is_space(line[index])))
			space_flag = 1;
	}
	if (space_flag)
		seperate_meta(&line[start_index], index - start_index, list);
}

int	repeat_meta(const char *line, size_t index)
{
	if (index > 0)
		if (!ft_strncmp(&line[index - 1], "<<" , 2) || !ft_strncmp(&line[index - 1], ">>", 2))
			return (1);
	return (0);
}

int	split_delimiter(const char *line, t_list **list)
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
			split_space(&line[start_index], index - start_index, list);
			start_index = index;
		}
	}
	split_space(&line[start_index], index - start_index, list);
	if (quote_flag)
		return (0);
	return (1);
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

void	scan_command(const char* line)
{
	t_list *list;

	list = NULL;
	split_delimiter(line, &list);
	// search_list(list);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command_line;

	while (1)
	{
		command_line = readline("minishell> ");
		if (!command_line)
			break ;
		scan_command(command_line);
		add_history(command_line);
		free(command_line);
		command_line = NULL;
	}
	return (0);
}
