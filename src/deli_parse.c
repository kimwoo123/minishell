/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deli_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:45:52 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/06 12:03:45 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

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

static int	is_quote(const char c)
{
	return (c == '\'' || c == '\"');
}

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	index;

	result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (result == NULL)
		return (NULL);
	index = 0;
	while (str[index])
		result[index] = str[index++];
	result[index] = '\0';
	return (result);
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

char	*ft_strchr(const char *str, int c)
{
	while (*str != (char)c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
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
		result[index] = begin[index++];
	result[index] = '\0';
	return (result);
}

void	check_quote(const char c, char *flag)
{
	if (*flag && *flag == c)
		*flag = '\0';
	else if (!*flag && is_quote(c))
		*flag = c;
}

void	get_token(const char *line, size_t size)
{
	printf("token: %s\n", ft_strndup(line, size));
}

void	seperate_meta(const char *line, size_t size)
{
	size_t	index;
	size_t	start_index;

	index = trim_line(&line[0]);
	start_index = index;
	if (is_delimiter(line[index]))
	{
		while (index < size && is_delimiter(line[index]))
			index++;
		get_token(&line[start_index], index - start_index);
		if (size != index)
			get_token(&line[index], size - index);
	}
	else
		get_token(&line[index], size - index);
}

// space 기준으로 분리
void	split_space(const char *line, size_t size)
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
		check_quote(line[index], &quote_flag);
		if (!quote_flag && (space_flag && is_space(line[index])))
		{
			seperate_meta(&line[start_index], index - start_index);
			start_index = index;
			space_flag = 0;
		}
		else if (!quote_flag && (!space_flag && !is_space(line[index])))
			space_flag = 1;
	}
	if (space_flag)
		seperate_meta(&line[start_index], index - start_index);
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
int	scan_command(const char *line)
{
	size_t	index;
	size_t	start_index;
	char	quote_flag;

	quote_flag = '\0';
	start_index = 0;
	index = -1;
	while (line[++index])
	{
		check_quote(line[index], &quote_flag);
		if ((!quote_flag && is_delimiter(line[index])) && !repeat_meta(line, index))
		{
			split_space(&line[start_index], index - start_index);
			start_index = index;
		}
	}
	split_space(&line[start_index], index - start_index);
	if (quote_flag)
		return (0);
	return (1);
}
