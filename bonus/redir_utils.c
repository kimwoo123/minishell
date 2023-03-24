/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:31 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 15:42:33 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*join_redirection(t_tree *tree)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(tree->left->content, " ");
	if (temp == NULL)
		return (NULL);
	new_str = ft_strjoin(temp, tree->right->content);
	if (new_str == NULL)
		return (NULL);
	free(temp);
	return (new_str);
}

int	split_redirection(t_data *data, t_tree *tree)
{
	char	*temp;

	temp = join_redirection(tree);
	if (temp == NULL)
		return (FAILURE);
	data->commands = ft_split(temp, ' ');
	if (data->commands == NULL)
		return (FAILURE);
	free(temp);
	return (SUCCESS);
}
