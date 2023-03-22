/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:45:26 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/22 10:25:17 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_variable(char *str, t_data *data)
{
	size_t		index;
	char		*env;
	char		*result;
	char		*temp;
	extern int	g_status;

	index = 1;
	env = ft_getenv(data->copied_envp, &str[index]);
	if (!ft_strncmp(str, "$", ft_strlen(str)))
		result = ft_strdup("$");
	else if (str[index] == '?')
	{
		temp = ft_itoa(WEXITSTATUS(g_status));
		result = ft_strdup(temp);
		free(temp);
	}
	else if (!env)
		result = ft_strdup("");
	else
		result = ft_strdup(env);
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

char	*convert_dollar(char **str, t_data *data)
{
	char	*result;
	char	*temp;
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (*str[index] == DOLLAR)
		{
			temp = str[index];
			str[index] = convert_variable(str[index], data);
			free(temp);
		}
		++index;
	}
	result = merge_str(str);
	return (result);
}

char	*expand_str(const char *line, size_t size, t_data *data)
{
	char	**temp;
	char	*result;

	temp = split_dollar(line, size);
	result = convert_dollar(temp, data);
	free_double(temp);
	return (result);
}
