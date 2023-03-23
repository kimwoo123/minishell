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
		pwd_command(data);
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

static size_t	get_cmd_size(t_tree *tree)
{
	size_t	size;
	t_tree	*temp;

	size = 1;
	temp = tree->right;
	while (temp != NULL)
	{
		if (temp->left != NULL)
			++size;
		temp = temp->right;
	}
	return (size);
}

static char	**join_command(t_tree *tree)
{
	size_t	size;
	size_t	index;
	t_tree	*temp;
	char	**result;

	size = get_cmd_size(tree);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = NULL;
	index = 0;
	result[index++] = ft_strdup(tree->left->content);
	temp = tree->right;
	while (temp != NULL)
	{
		if (temp->left != NULL)
			result[index++] = ft_strdup(temp->left->content);
		temp = temp->right;
	}
	return (result);
}

int	do_command(t_data *data, t_tree *tree)
{
	data->commands = join_command(tree);
	if (data->has_forked == FALSE \
	&& is_builtin(data->commands[0]) == TRUE)
		execve_builtin(data);
	else
		do_fork(data);
	return (SUCCESS);
}
