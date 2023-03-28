/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deli_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:45:52 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/28 10:00:26 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	seperate_meta(const char *line, size_t size, t_list **list, t_data *d)
{
	size_t	index;
	size_t	start_index;

	index = trim_line(line);
	start_index = index;
	if (is_delimiter(line[index]))
	{
		while (index < size && is_delimiter(line[index]))
			index++;
		tokenize(&line[start_index], index - start_index, list, d);
		if (size != index)
			tokenize(&line[index], size - index, list, d);
	}
	else
		tokenize(&line[index], size - index, list, d);
}

void	split_space(const char *line, size_t size, t_list **list, t_data *data)
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
			seperate_meta(&line[start_index], index - start_index, list, data);
			start_index = index;
			space_flag = 0;
		}
		else if (!quote_flag && (!space_flag && !is_space(line[index])))
			space_flag = 1;
	}
	if (space_flag)
		seperate_meta(&line[start_index], index - start_index, list, data);
}

int	repeat_meta(const char *line, size_t index, size_t *flag)
{
	if (*flag == 0)
	{
		if (is_subshell(line[index]))
			return (FALSE);
		if (index > 0)
		{
			if (line[index - 1] == line[index])
			{
				*flag = 1;
				return (TRUE);
			}
		}
	}
	else
		*flag = 0;
	return (FALSE);
}

void	split_delimiter(const char *line, t_list **list, t_data *data)
{
	size_t	index;
	size_t	repeat_flag;
	size_t	start_index;
	char	quote_flag;

	quote_flag = '\0';
	start_index = 0;
	index = -1;
	repeat_flag = 0;
	while (line[++index])
	{
		quote_flag = check_quote(line[index], quote_flag);
		if ((!quote_flag && is_delimiter(line[index])) && \
		!repeat_meta(line, index, &repeat_flag))
		{
			split_space(&line[start_index], index - start_index, list, data);
			start_index = index;
		}
	}
	split_space(&line[start_index], index - start_index, list, data);
}

t_list	*scan_command(const char *line, t_data *data)
{
	t_list	*list;
	int		accept;

	list = NULL;
	if (close_quote(line) == FALSE)
	{
		ft_putendl_fd("quote error", STDERR_FILENO);
		return (NULL);
	}
	split_delimiter(line, &list, data);
	accept = check_syntax(&list);
	if (accept == FALSE)
	{
		free_list(&list);
		return (NULL);
	}
	return (list);
}
