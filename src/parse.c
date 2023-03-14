/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:36:39 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/12 09:48:14 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DELIMETER "<>|"

char *ft_strndup(char *begin, char *end)
{
	// only (begin TO end) duplicate
}
char **get_token(char *begin)
{
	char *end;
	char *line;

	line = begin;
	end = NULL;
	if (!ft_strncmp("<<", line, 2))
		line += 1;
	else if (!ft_strncmp(">>", line, 3))
		line += 1;
	else if (*line == '|')
		return (ft_strdup("|"));
	while (*line)
	{
		if (ft_strchr(*line, DELIMETER))
			break ;
		line += 1;
	}
	end = line;
	return (ft_strndup(begin, end));
}

int	parse_cmd(char *line)
{
	char flag;

	flag = 0;
	while (*line)
	{
		if (flag && *line == flag)
			flag = 0;
		else if (!flag && (*line == '\"' || *line == '\"'))
			flag = *line;
		if (!flag && ft_strchr(*line, DELIMETER))
		{

		}
		line+= 1;
	}
	if (flag != 0)
		return (1);
}
