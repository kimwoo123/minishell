/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:05:47 by chajung           #+#    #+#             */
/*   Updated: 2023/03/13 10:05:48 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chdir(const char *path, const char *cmd)
{
	char	*error_str;

	if (chdir(path) == FAILURE)
	{
		if (cmd == NULL)
			perror("bash: cd: "); //need to fix
		else
		{
			error_str = ft_strjoin("bash: cd: ", cmd);
			if (error_str == NULL)
				ft_perror("strjoin error in ft_chdir function", EXIT_FAILURE);
			perror(error_str);
		}
	}
}

char	*find_home_path(char **envp)
{
	size_t	index;

	if (!envp)
		return (NULL);
	index = 0;
	while (envp[index] && ft_strncmp(envp[index], "HOME=", ft_strlen("HOME=")))
		index++;
	if (!envp[index] || ft_strncmp(envp[index], "HOME=", ft_strlen("HOME=")))
		return (NULL);
	return (&(envp)[index][5]);
}
