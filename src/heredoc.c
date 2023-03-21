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

int	preprocess_heredoc(t_data *data, t_tree *tree)
{	
	char	*str_with_nl;
	char	*delimiter;
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
		str_with_nl = ft_strjoin(temp, "\n");
		if (str_with_nl == NULL)
			return (FAILURE);
		free(temp);
		delimiter = ft_strjoin(data->commands[1], "\n");
		if (delimiter == NULL)
			return (FAILURE);
		if (is_equal_to(str_with_nl, delimiter) == TRUE)
		{
			free(str_with_nl);
			free(delimiter);
			break ;
		}
		expand = expand_str_hd(str_with_nl);
		temp = save;
		save = ft_strjoin(temp, expand);
		if (save == NULL)
			return (FAILURE);
		free(expand);
		free(temp);
		free(str_with_nl);
		free(delimiter);
	}
	free(tree->right->content);
	tree->right->content = save;
	return (SUCCESS);
}

// static int	check_equal(char *input_line, char *delim)
// {
// 	input_line = ft_strjoin(input_line, "\n");
// 	if (input_line == NULL)
// 		return (FAILURE);
// 	delim = ft_strjoin(delim, "\n");
// 	if (delim == NULL)
// 		return (FAILURE);
// 	if (is_equal_to(input_line, delim) == TRUE)
// 	{
// 		free(input_line);
// 		free(delim);
// 		return (TRUE);
// 	}
// 	free(input_line);
// 	free(delim);
// 	return (FAILURE);
// }

// static void	free_each(char *str1, char *str2)
// {
// 	free(str1);
// 	free(str2);
// }

// int	preprocess_heredoc(t_data *data, t_tree *tree)
// {	
// 	char	*expand;
// 	char	*save;
// 	char	*temp;

// 	save = ft_strdup("");
// 	if (save == NULL)
// 		return (FAILURE);
// 	while (1)
// 	{
// 		temp = readline("> ");
// 		if (temp == NULL)
// 			break ;
// 		if (check_equal(temp, data->commands[1]) == TRUE)
// 			break ;
// 		free(temp);
// 		expand = expand_str_hd(temp);
// 		temp = save;
// 		save = ft_strjoin(temp, expand);
// 		if (save == NULL)
// 			return (FAILURE);
// 		free_each(temp, expand);
// 	}
// 	// free(tree->right->content);
// 	tree->right->content = save;
// 	return (SUCCESS);
// }
