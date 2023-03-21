/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:01:06 by chajung           #+#    #+#             */
/*   Updated: 2023/03/21 10:08:49 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str_hd(const char *line)
{
	char	**temp;
	char	*result;

	temp = split_dollar_hd(line);
	result = convert_dollar(temp);
	free_double(temp);
	return (result);
}

int	check_equal(char *input_line, char *delim)
{
	input_line = ft_strjoin(input_line, "\n");
	if (temp == NULL)
		return (FAILURE);
	delim = ft_strjoin(delim, "\n");
	if (delim == NULL)
		return (FAILURE);
	if (is_equal_to(input_line, delim) == TRUE)
	{
		free(temp);
		free(delim);
		return (TRUE);
	}
	free(temp);
	free(delim);
	return (FAILURE);
}

static void	free_each(char *str1, char *str2, char *str3, char *str4)
{
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

int	preprocess_heredoc(t_data *data, t_tree *tree)
{	
	char	*expand;
	char	*save;
	char	*temp;

	save = ft_strdup("");
	if (save == NULL)
		return (FAILURE);
	while (1)
	{
		temp = readline("> ");
		if (temp == NULL)
			break ;
		if (check_equal(temp, data->command[1]) == TRUE)
			break;
		free(temp);
		expand = expand_str_hd(str_with_nl);
		temp = save;
		save = ft_strjoin(temp, expand);
		if (save == NULL)
			return (FAILURE);
		free_each(temp, expand, str_with_nl, delimiter);
	}
	free(tree->right->content);
	tree->right->content = save;
	return (SUCCESS);
}
