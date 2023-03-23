/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:57:44 by chajung           #+#    #+#             */
/*   Updated: 2023/03/21 09:18:32 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static size_t	get_dollar_len_hd(const char *line)
{
	size_t	index;

	index = 1;
	if (!line[index])
		return (index);
	if (line[index] == '?')
		return (++index);
	if (line[index] == DOLLAR)
		return (++index);
	while ((line[index] && line[index] != DOLLAR) && \
		(!is_quote(line[index]) && !is_space(line[index])))
		++index;
	return (index);
}

static size_t	get_dollar_index_hd(const char *line)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == DOLLAR)
			return (index);
		++index;
	}
	return (index);
}

static void	duplicate_str_hd(char **result, const char *line)
{
	size_t	s_index;
	size_t	index;
	int		dollar_flag;

	index = 0;
	dollar_flag = 1;
	if (*line == DOLLAR)
		dollar_flag = 0;
	while (line[index])
	{
		if (!dollar_flag && line[index] == DOLLAR)
		{
			dollar_flag = 1;
			s_index = index;
			index += get_dollar_len_hd(&line[index]);
			*(result++) = ft_strndup(&line[s_index], index - s_index);
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			s_index = index;
			index += get_dollar_index_hd(&line[index]);
			*(result++) = ft_strndup(&line[s_index], index - s_index);
		}
	}
}

static size_t	double_array_size_hd(const char *line)
{
	int		dollar_flag;
	size_t	size;
	size_t	index;

	index = 0;
	size = 0;
	dollar_flag = 1;
	if (*line == DOLLAR)
		dollar_flag = 0;
	while (line[index])
	{
		if (!dollar_flag && line[index] == '$')
		{
			dollar_flag = 1;
			index += get_dollar_len_hd(&line[index]);
			++size;
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			index += get_dollar_index_hd(&line[index]);
			++size;
		}
	}
	return (size);
}

char	**split_dollar_hd(const char *line)
{
	char	**result;
	size_t	r_size;

	r_size = double_array_size_hd(line);
	result = (char **)malloc(sizeof(char *) * (r_size + 1));
	duplicate_str_hd(result, line);
	result[r_size] = NULL;
	return (result);
}
