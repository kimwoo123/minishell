/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deli_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:45:52 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 15:47:43 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list	*scan_command(const char *line)
{
	t_list *list;

	if (close_quote(line) == 0)
	{
		printf("quote error");
		exit(1);
	}
	list = NULL;
	split_delimiter(line, &list);
	/* add test code */
	//test_tree(&list);
	test_code(&list);
	/* add test code */
	return (list);
}
