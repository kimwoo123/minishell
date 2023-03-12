/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:12 by chajung           #+#    #+#             */
/*   Updated: 2023/03/02 14:19:13 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd_command(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_perror("pwd error", EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	path = NULL;
	return (0);
}
