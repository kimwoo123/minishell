/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:45:26 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/22 12:44:15 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	if (result == NULL)
		return (NULL);
	return (result);
}

char	*merge_str(char **split_str)
{
	char	*result;
	char	*temp;
	size_t	index;

	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	index = 0;
	while (split_str[index])
	{
		temp = result;
		result = ft_strjoin(result, split_str[index]);
		if (result == NULL)
			return (NULL);
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
			if (str[index] == NULL)
				return (NULL);
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
	if (temp == NULL)
		exit_with_str("malloc error in expand_str", EXIT_FAILURE);
	result = convert_dollar(temp, data);
	if (result == NULL)
		exit_with_str("malloc error in expand_str", EXIT_FAILURE);
	free_double(temp);
	return (result);
}