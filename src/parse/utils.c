/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:44:33 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 18:13:53 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"


int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*ft_strndup(const char *begin, size_t size)
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
