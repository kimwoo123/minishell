/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:42:50 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 15:53:39 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	trim_line(const char *line)
{
	size_t	index;

	index = 0;
	while (line[index] && is_space(line[index]))
		index++;
	return (index);
}

int	is_delimiter(const char c)
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

char	check_quote(const char c, char flag)
{
	if (flag && flag == c)
		return ('\0');
	else if (!flag && is_quote(c))
		return (c);
	return (flag);
}

int	close_quote(const char *line)
{
	char	quote_flag;
	size_t	index;

	quote_flag = '\0';
	index = 0;
	while (line[index])
	{
		quote_flag = check_quote(line[index], quote_flag);
		++index;
	}
	if (quote_flag != '\0')
		return (0);
	return (1);
}
