/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:38:42 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/22 13:45:32 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

size_t	get_dollar_len(const char *line)
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

size_t	get_dollar_index(const char *line, char *quote_flag)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		*quote_flag = check_quote(line[index], *quote_flag);
		if (*quote_flag != '\'' && line[index] == DOLLAR)
			return (index);
		++index;
	}
	return (index);
}

size_t	double_array_size(const char *line, char *quote_flag)
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
		if (!dollar_flag && (*quote_flag != '\'' && line[index] == '$'))
		{
			dollar_flag = 1;
			index += get_dollar_len(&line[index]);
			++size;
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			index += get_dollar_index(&line[index], quote_flag);
			++size;
		}
	}
	return (size);
}

void	duplicate_str(char **result, const char *line, char *quote_flag)
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
		if (!dollar_flag && (*quote_flag != '\'' && line[index] == DOLLAR))
		{
			dollar_flag = 1;
			s_index = index;
			index += get_dollar_len(&line[index]);
			*(result++) = ft_strndup(&line[s_index], index - s_index);
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			s_index = index;
			index += get_dollar_index(&line[index], quote_flag);
			*(result++) = ft_strndup(&line[s_index], index - s_index);
		}
	}
}

char	**split_dollar(const char *line, size_t size)
{
	char	*temp;
	char	**result;
	size_t	r_size;
	size_t	index;
	char	quote_flag;

	quote_flag = '\0';
	temp = ft_strndup(line, size);
	r_size = double_array_size(temp, &quote_flag);
	result = (char **)malloc(sizeof(char *) * (r_size + 1));
	if (result == NULL)
		return (NULL);
	duplicate_str(result, temp, &quote_flag);
	index = 0;
	while (index < r_size)
	{
		if (result[index] == NULL)
			return (NULL);
		++index;
	}
	result[r_size] = NULL;
	free(temp);
	return (result);
}
