/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:45:26 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/12 18:26:27 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	while (line[index] && (!is_quote(line[index]) && !is_space(line[index])))
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
	size_t	r_index;
	int		dollar_flag;

	s_index = 0;
	r_index = 0;
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
			result[r_index++] = ft_strndup(&line[s_index], index - s_index);
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			s_index = index;
			index += get_dollar_index(&line[index], quote_flag);
			result[r_index++] = ft_strndup(&line[s_index], index - s_index);
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

char	*convert_variable(char *str)
{
	size_t	index;
	char	*env;
	char	*result;

	index = 1;
	env = getenv(&str[index]);
	if (str[index] == '?')
		result = ft_strdup("signal");
	else if (!env)
		result = ft_strdup("");
	else
		result = ft_strdup(env);;
	free(str);
	return (result);
}

char	*merge_str(char **split_str)
{
	char	*result;
	char	*temp;
	size_t	index;

	result = ft_strdup("");
	index = 0;
	while(split_str[index])
	{
		temp = result;
		result = ft_strjoin(result, split_str[index]);
		free(temp);
		++index;
	}
	return (result);
}

char	*convert_merge(char **split_str)
{
	char	*result;
	char	*temp;
	size_t	index;

	index = 0;
	while (split_str[index])
	{
		if (*split_str[index] == '$')
			split_str[index] = convert_variable(split_str[index]);
		index++;
	}
	temp = merge_str(split_str);
	result = remove_quote(temp);
	free_double(split_str);
	return (result);
}

char	*convert_dollar(char const *line, size_t size)
{
	char	**temp;
	char	*token;

	temp = split_dollar(line, size);
	token = convert_merge(temp);
	return (token);
}
