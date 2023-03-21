/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:01:06 by chajung           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/21 09:01:01 by wooseoki         ###   ########.fr       */
=======
/*   Updated: 2023/03/20 15:30:43 by wooseoki         ###   ########.fr       */
>>>>>>> 27a77c9b84c7eb9ecd7383e896c035f5865d5273
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
		free(temp);
		free(expand);
		free(str_with_nl);
		free(delimiter);
	}
	free(tree->right->content);
	tree->right->content = save;
	return (SUCCESS);
}
