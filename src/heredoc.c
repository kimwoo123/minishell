/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:01:06 by chajung           #+#    #+#             */
/*   Updated: 2023/03/05 11:01:09 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_doc(t_data *data)
{
	int		fd;
	char	*str;
	char	*str_with_newline;
	char	*delimiter;

	fd = ft_open("heredoc_temp", (O_WRONLY | O_CREAT | O_TRUNC), 0644);
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			break ;
		str_with_newline = ft_strjoin(str, "\n");
		if (str_with_newline == NULL)
			ft_perror("strjoin error in heredoc", EXIT_FAILURE);
		free(str);
		delimiter = ft_strjoin(data->commands[1], "\n");
		if (delimiter == NULL)
			ft_perror("strjoin error in heredoc", EXIT_FAILURE);
		if (ft_strlen(str_with_newline) == ft_strlen(delimiter) \
			&& !ft_strncmp(str_with_newline, delimiter, ft_strlen(str_with_newline)))
		{
			free(str_with_newline);
			free(delimiter);
			break ;
		}
		write(fd, str_with_newline, ft_strlen(str_with_newline));
		free(str_with_newline);
		free(delimiter);
	}
	ft_close(fd);
	// ft_unlink("heredoc_temp");
	return (0);
}
