/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:21:20 by chajung           #+#    #+#             */
/*   Updated: 2023/03/27 16:45:43 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

static char	**join_command(t_tree *tree)
{
	char	**result;
	size_t	size;
	size_t	new_size;
	size_t	wc_flag;

	wc_flag = 0;
	size = get_cmd_size(tree, &wc_flag);
	new_size = size + wc_flag;
	result = (char **)ft_calloc(sizeof(char *), (new_size + 1));
	if (result == NULL)
		return (NULL);
	result[size] = NULL;
	if (make_commands_wc(tree, result, wc_flag) == FAILURE)
		return (NULL);
	return (result);
}

int	do_command(t_data *data, t_tree *tree)
{
	if (data->no_cmd == FALSE)
	{
		data->commands = join_command(tree);
		if (data->commands == NULL)
			exit_with_str("malloc error in do command", EXIT_FAILURE);
		if (data->sub_flag == FALSE && (data->has_forked == FALSE \
		&& is_builtin(data->commands[0]) == TRUE))
		{
			data->pid = -1;
			execve_builtin(data);
		}
		else
			do_fork(data);
	}
	else
		do_fork(data);
	return (SUCCESS);
}
