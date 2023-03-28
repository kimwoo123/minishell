/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:42:49 by chajung           #+#    #+#             */
/*   Updated: 2023/03/27 17:01:12 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	ft_chdir(const char *path, const char *cmd)
{
	char	*error_str;

	if (chdir(path) == FAILURE)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(error_str);
		set_status(EXIT_FAILURE);
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
