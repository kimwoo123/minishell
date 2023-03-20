/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:45:26 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/20 15:34:10 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*convert_variable(char *str)
{
	size_t		index;
	char		*env;
	char		*result;
	extern int	g_status;

	index = 1;
	env = getenv(&str[index]);
	if (!ft_strncmp(str, "$", ft_strlen(str)))
		result = ft_strdup("$");
	if (str[index] == '?')
		result = ft_strdup(ft_itoa(WEXITSTATUS(g_status)));
	else if (!env)
		result = ft_strdup("");
	else
		result = ft_strdup(env);
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
	while (split_str[index])
	{
		temp = result;
		result = ft_strjoin(result, split_str[index]);
		free(temp);
		++index;
	}
	return (result);
}

char	*convert_dollar(char **str)
{
	char	*result;
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (*str[index] == DOLLAR)
			str[index] = convert_variable(str[index]);
		++index;
	}
	result = merge_str(str);
	free_double(str);
	return (result);
}

char	*expand_str(const char *line, size_t size)
{
	char	**temp;
	char	*result;

	temp = split_dollar(line, size);
	result = convert_dollar(temp);
	return (result);
}
