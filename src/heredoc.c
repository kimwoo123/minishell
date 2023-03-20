/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:01:06 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 11:21:40 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_dollar_len_hd(const char *line)
{
	size_t	index;

	index = 1;
	if (!line[index])
		return (index);
	if (line[index] == '?')
		return (++index);
	if (line[index] == DOLLAR)
		return (++index);
	while ((line[index] && line[index] != DOLLAR) && \
		(!is_quote(line[index]) && !is_space(line[index])))
		++index;
	return (index);
}

size_t	get_dollar_index_hd(const char *line)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == DOLLAR)
			return (index);
		++index;
	}
	return (index);
}

void	duplicate_str_hd(char **result, const char *line)
{
	size_t	s_index;
	size_t	index;
	int		dollar_flag;

	index = 0;
	dollar_flag = 1;
	if (*line == DOLLAR)
		dollar_flag = 0;
	while (line[index])
	{
		if (!dollar_flag && line[index] == DOLLAR)
		{
			dollar_flag = 1;
			s_index = index;
			index += get_dollar_len_hd(&line[index]);
			*(result++) = ft_strndup(&line[s_index], index - s_index);
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			s_index = index;
			index += get_dollar_index_hd(&line[index]);
			*(result++) = ft_strndup(&line[s_index], index - s_index);
		}
	}
}

size_t	double_array_size_hd(const char *line)
{
	int		dollar_flag;
	size_t	size;
	size_t	index;

	index = 0;
	size = 0;
	dollar_flag = 1;
	if (*line == DOLLAR)
		dollar_flag = 0;
	while (line[index])
	{
		if (!dollar_flag && line[index] == '$')
		{
			dollar_flag = 1;
			index += get_dollar_len_hd(&line[index]);
			++size;
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			index += get_dollar_index_hd(&line[index]);
			++size;
		}
	}
	return (size);
}

char	**split_dollar_hd(const char *line)
{
	char	*temp;
	char	**result;
	size_t	r_size;

	r_size = double_array_size_hd(line);
	result = (char **)malloc(sizeof(char *) * (r_size + 1));
	duplicate_str_hd(result, line);
	result[r_size] = NULL;
	return (result);
}

char	*expand_str_hd(const char *line)
{
	char	**temp;
	char	*result;

	temp = split_dollar_hd(line);
	result = convert_dollar(temp);
	return (result);
}

int	here_doc(t_data *data)
{
	int		heredoc_fd;
	char	*str;
	char	*str_with_newline;
	char	*delimiter;
	char	*expand;

	heredoc_fd = ft_open("heredoc_temp", (O_WRONLY | O_CREAT | O_TRUNC), 0644);
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
		expand = expand_str_hd(str_with_newline);
		write(heredoc_fd, expand, ft_strlen(expand));
		free(str_with_newline);
		free(delimiter);
	}
	ft_close(heredoc_fd);
	// ft_unlink("heredoc_temp");
	return (0);
}
