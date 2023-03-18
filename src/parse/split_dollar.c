/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:38:42 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 16:23:36 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_dollar_len(char const *line)
{
	size_t	index;

	index = 1;
	if (!line[index])
		return (index);
	if (line[index] == '?')
		return (++index);
	if (line[index] == '$')
		return (++index);
	while ((line[index] && line[index] != '$') && \
		(!is_quote(line[index]) && !is_space(line[index])))
		index++;
	return (index);
}

size_t	get_dollar_index(char const *line, char *quote_flag)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		*quote_flag = check_quote(line[index], *quote_flag);
		if (*quote_flag != '\'' && line[index] == '$')
			return (index);
		index++;
	}
	return (index);
}

size_t	double_array_size(char const *line, char *quote_flag)
{
	int		dollar_flag;
	size_t	size;
	size_t	index;

	index = 0;
	size = 0;
	dollar_flag = 1;
	if (*line == '$')
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

void	duplicate_str(char **result, char *line, char *quote_flag)
{
	size_t	s_index;
	size_t	index;
	int		dollar_flag;

	index = 0;
	dollar_flag = 1;
	if (*line == '$')
		dollar_flag = 0;
	while (line[index])
	{
		if (!dollar_flag && (*quote_flag != '\'' && line[index] == '$'))
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

char	**split_dollar(char const *line, size_t size)
{
	char	*temp;
	char	**result;
	size_t	r_size;
	char	quote_flag;

	quote_flag = '\0';
	temp = ft_strndup(line, size);
	r_size = double_array_size(temp, &quote_flag);
	result = (char **)malloc(sizeof(char *) * (r_size + 1));
	duplicate_str(result, temp, &quote_flag);
	result[r_size] = NULL;
	free(temp);
	return (result);
}
