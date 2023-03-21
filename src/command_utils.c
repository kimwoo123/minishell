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
		exit_with_str("malloc error in do command", EXIT_FAILURE);
	data->commands = ft_split(temp, ' ');
	if (data->commands == NULL)
		exit_with_str("malloc error in do command", EXIT_FAILURE);
	free(temp);
	if (data->has_forked == FALSE \
	&& is_builtin(data->commands[0]) == TRUE)
		execve_builtin(data);
	else
		do_fork(data);
	return (SUCCESS);
}
