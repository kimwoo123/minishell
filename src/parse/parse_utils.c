/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:42:50 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/25 10:50:52 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

size_t	trim_line(const char *line)
{
	size_t	index;

	index = 0;
	while (line[index] && is_space(line[index]))
		index++;
	return (index);
}

int	is_subshell(char c)
{
	return (c == '(' || c == ')');
}

int	is_delimiter(char c)
{
	int	index;

	index = 0;
	while (DELIMITER[index])
	{
		if (DELIMITER[index] == c)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

char	check_quote(char c, char flag)
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
		return (FALSE);
	return (TRUE);
}
