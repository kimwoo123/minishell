/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:21:20 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 16:21:22 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_builtin(t_data *data)
{
	int	result;

	result = FAILURE;
	if (is_equal_to(data->commands[0], "echo") == SAME)
		result = echo_command(data->commands);
	else if (is_equal_to(data->commands[0], "cd") == SAME)
		result = cd_command(data);
	else if (is_equal_to(data->commands[0], "pwd") == SAME)
		result = pwd_command(data);
	else if (is_equal_to(data->commands[0], "export") == SAME)
		result = export_command(data);
	else if (is_equal_to(data->commands[0], "unset") == SAME)
		result = unset_command(data);
	else if (is_equal_to(data->commands[0], "env") == SAME)
		result = env_command(data);
	else if (is_equal_to(data->commands[0], "exit") == SAME)
		result = exit_command(data);
	return (result);
}

int	is_builtin(char *str)
{
	if (is_equal_to(str, "echo") == SAME \
	|| is_equal_to(str, "cd") == SAME \
	|| is_equal_to(str, "pwd") == SAME \
	|| is_equal_to(str, "export") == SAME \
	|| is_equal_to(str, "unset") == SAME \
	|| is_equal_to(str, "env") == SAME \
	|| is_equal_to(str, "exit") == SAME)
		return (FOUND);
	return (NOT_FOUND);
}

static char	*ft_strjoin_wspace(char *str1, char *str2)
{
	char	*temp;
	char	*new_str;

	temp = ft_strjoin(str1, " ");
	if (temp == NULL)
		return (NULL);
	new_str = ft_strjoin(temp, str2);
	if (new_str == NULL)
		return (NULL);
	free(temp);
	return (new_str);
}

static char	*join_command(t_tree *tree)
{
	char	*str;
	char	*new_str;
	t_tree	*temp;

	str = ft_strdup(tree->left->content);
	if (str == NULL)
		return (NULL);
	temp = tree->right;
	while (temp != NULL)
	{
		if (temp->left != NULL)
		{
			new_str = ft_strjoin_wspace(str, temp->left->content);
			if (new_str == NULL)
				return (NULL);
			free(str);
			str = new_str;
			new_str = NULL;
		}
		temp = temp->right;
	}
	return (str);
}

int	do_command(t_data *data, t_tree *tree)
{
	char	*temp;

	temp = join_command(tree);
	if (temp == NULL)
		return (FAILURE);
	data->commands = ft_split(temp, ' ');
	if (data->commands == NULL)
		return (FAILURE);
	free(temp);
	if (data->has_forked == FALSE \
	&& is_builtin(data->commands[0]) == TRUE)
		execve_builtin(data);
	else
		is_not_builtin(data);
	return (SUCCESS);
}
