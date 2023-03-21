/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:01:06 by chajung           #+#    #+#             */
/*   Updated: 2023/03/21 10:10:56 by wooseoki         ###   ########.fr       */
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

int	each_strjoin_compare(t_data *data, char **temp, char **str_nl, char **delim)
{
	*str_nl = ft_strjoin(*temp, "\n");
	if (*str_nl == NULL)
		return (FAILURE);
	free(*temp);
	*delim = ft_strjoin(data->commands[1], "\n");
	if (*delim == NULL)
		return (FAILURE);
	if (is_equal_to(*str_nl, *delim) == TRUE)
	{
		free(*str_nl);
		free(*delim);
		return (FAILURE);
	}
	return (SUCCESS);
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
	char	*str_nl;
	char	*delim;
	char	*expand;
	char	*save;
	char	*temp;

	save = ft_strdup("");
	if (save == NULL)
		return (FAILURE);
	while (1)
	{
		temp = readline("> ");
		if (temp == NULL \
		|| each_strjoin_compare(data, &temp, &str_nl, &delim) == FAILURE)
			break ;
		expand = expand_str_hd(str_nl);
		temp = save;
		save = ft_strjoin(temp, expand);
		if (save == NULL)
			return (FAILURE);
		free_each(expand, temp, str_nl, delim);
	}
	free(tree->right->content);
	tree->right->content = save;
	return (SUCCESS);
}
