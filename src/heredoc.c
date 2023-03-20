/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:01:06 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 15:30:43 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_hd(const char *line)
{
	char	**temp;
	char	*result;

	temp = split_dollar_hd(line);
	result = convert_dollar(temp);
	return (result);
}

int	preprocess_heredoc(t_data *data, t_tree *tree)
{	
	char	*str;
	char	*str_with_newline;
	char	*delimiter;
	char	*expand;
	char	*save;
	char	*temp;

	save = ft_strdup("");
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
		if (is_equal_to(str_with_newline, delimiter) == TRUE)
		{
			free(str_with_newline);
			free(delimiter);
			break ;
		}
		expand = expand_str_hd(str_with_newline);
		temp = save;
		save = ft_strjoin(temp, str_with_newline);
		free(temp);
		free(str_with_newline);
		free(delimiter);
	}
	free(tree->right->content);
	tree->right->content = save;
	save = NULL;
	return (0);
}
