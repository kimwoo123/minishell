/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:44:33 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 15:45:07 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
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
