/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:21:20 by chajung           #+#    #+#             */
/*   Updated: 2023/03/23 09:58:29 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_builtin(t_data *data)
{
	if (is_equal_to(data->commands[0], "echo"))
		echo_command(data->commands);
	else if (is_equal_to(data->commands[0], "cd"))
		cd_command(data);
	else if (is_equal_to(data->commands[0], "pwd"))
		pwd_command();
	else if (is_equal_to(data->commands[0], "export"))
		export_command(data);
	else if (is_equal_to(data->commands[0], "unset"))
		unset_command(data);
	else if (is_equal_to(data->commands[0], "env"))
		env_command(data);
	else if (is_equal_to(data->commands[0], "exit"))
		exit_command(data);
}

int	is_builtin(char *str)
{
	if (is_equal_to(str, "echo") \
	|| is_equal_to(str, "cd") \
	|| is_equal_to(str, "pwd") \
	|| is_equal_to(str, "export") \
	|| is_equal_to(str, "unset") \
	|| is_equal_to(str, "env") \
	|| is_equal_to(str, "exit"))
		return (TRUE);
	return (FALSE);
}

#include <dirent.h>
#include "minishell.h"

// if count == 0, do not convert wild card.
// use count like flag
int	count_wild_cards(size_t *wc_flag)
{
	// int				count;
	DIR				*dir;
	struct dirent	*entry;

 	dir = opendir(".");
	if (dir == NULL)
		return (FAILURE);
	// count = 0;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (is_equal_to(entry->d_name, ".") == FALSE \
		&& is_equal_to(entry->d_name, "..") == FALSE)
			(*wc_flag)++;
			// count++;
	}
	if (closedir(dir) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static size_t	get_cmd_size(t_tree *tree, size_t *wc_flag)
{
	size_t	size;
	t_tree	*temp;

	size = 1;
	temp = tree->right;
	while (temp != NULL)
	{
		if (temp->left != NULL)
		{
			if (is_equal_to(temp->left->content, "*") == TRUE)
				count_wild_cards(wc_flag);
			size++;
		}
		temp = temp->right;
	}
	return (size);
}

int	copy_tester(char **result, size_t *index)
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

static char	**join_command(t_tree *tree)
{
	size_t	size;
	size_t	index;
	t_tree	*temp;
	char	**result;

	size_t	wc_flag;
	size_t	new_size;

	wc_flag = 0;
	size = get_cmd_size(tree, &wc_flag);
	new_size = size + wc_flag;
	result = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = NULL;

	index = 0;
	temp = tree;
	while (temp != NULL)
	{
		if (temp->left != NULL)
		{
			if (is_equal_to(temp->left->content, "*") == TRUE)
			{
				if (wc_flag != 0)
					copy_tester(result, &index);
				else
				{
					result[index] = ft_strdup(temp->left->content);
					if (result[index] == NULL)
						return (NULL);
				}
			}
			else
			{
				result[index] = ft_strdup(temp->left->content);
				if (result[index] == NULL)
					return (NULL);
			}
			index++;
		}
		temp = temp->right;
	}
	return (result);
}

// static size_t	get_cmd_size(t_tree *tree)
// {
// 	size_t	size;
// 	t_tree	*temp;

// 	size = 1;
// 	temp = tree->right;
// 	while (temp != NULL)
// 	{
// 		if (temp->left != NULL)
// 			++size;
// 		temp = temp->right;
// 	}
// 	return (size);
// }

// static char	**join_command(t_tree *tree)
// {
// 	size_t	size;
// 	size_t	index;
// 	t_tree	*temp;
// 	char	**result;

// 	size = get_cmd_size(tree);
// 	result = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (result == NULL)
// 		return (NULL);
// 	result[size] = NULL;
// 	index = 0;
// 	result[index++] = ft_strdup(tree->left->content);
// 	temp = tree->right;
// 	while (temp != NULL)
// 	{
// 		if (temp->left != NULL)
// 			result[index++] = ft_strdup(temp->left->content);
// 		temp = temp->right;
// 	}
// 	return (result);
// }

int	do_command(t_data *data, t_tree *tree)
{
	data->commands = join_command(tree);
	if (data->has_forked == FALSE \
	&& is_builtin(data->commands[0]) == TRUE)
	{
		data->pid = -1;
		execve_builtin(data);
	}
	else
		do_fork(data);
	return (SUCCESS);
}
