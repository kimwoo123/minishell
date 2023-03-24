/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:11:54 by chajung           #+#    #+#             */
/*   Updated: 2023/03/24 11:11:55 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	copy_wild_cards(char **result, size_t *index)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		return (FAILURE);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (is_equal_to(entry->d_name, ".") == FALSE \
		&& is_equal_to(entry->d_name, "..") == FALSE)
		{
			result[*index] = ft_strdup(entry->d_name);
			if (result[*index] == NULL)
				return (FAILURE);
			(*index)++;
		}
	}
	if (closedir(dir) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	count_wild_cards(size_t *wc_flag)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		return (FAILURE);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (is_equal_to(entry->d_name, ".") == FALSE \
		&& is_equal_to(entry->d_name, "..") == FALSE)
			(*wc_flag)++;
	}
	if (closedir(dir) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	make_commands_wc(t_tree *tree, char **result, size_t wc_flag)
{
	t_tree	*temp;
	size_t	index;

	temp = tree;
	index = 0;
	while (temp != NULL)
	{
		if (temp->left != NULL)
		{
			if (wc_flag != 0 && is_equal_to(temp->left->content, "*") == TRUE)
			{
				if (copy_wild_cards(result, &index) == FAILURE)
					return (FAILURE);
			}
			else
			{
				result[index] = ft_strdup(temp->left->content);
				if (result[index] == NULL)
					return (FAILURE);
			}
			index++;
		}
		temp = temp->right;
	}
	return (SUCCESS);
}
