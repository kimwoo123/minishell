/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:40:59 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 10:31:50 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	do_pipe(t_data *data, t_tree *tree)
{
	data->redir_stat = FALSE;
	data->redir_out = FALSE;
	data->no_cmd = FALSE;
	data->count_cmd++;
	if (tree->right == NULL)
		data->last_cmd = TRUE;
	else if (tree->right != NULL)
	{
		data->has_forked = TRUE;
		if (pipe(data->pipe_fd) == FAILURE)
			exit_with_str("pipe error in do pipe", EXIT_FAILURE);
	}
}

static void	execve_command_line(t_data *data, t_tree *tree)
{
	if (tree->type == PIPE)
		do_pipe(data, tree);
	else if (tree->type == REDIRECTION)
	{
		do_redirection(data, tree);
		free_double_array(data->commands);
	}
	else if (tree->type == PARENT_CMD)
	{
		if (tree->left == NULL)
			data->no_cmd = TRUE;
		do_command(data, tree);
		if (data->no_cmd == FALSE)
			free_double_array(data->commands);
	}
}

void	search_tree(t_data *data, t_tree *head)
{
	if (head == NULL)
		return ;
	if (head->type == PIPE \
	|| head->type == REDIRECTION \
	|| head->type == PARENT_CMD)
		execve_command_line(data, head);
	if (head->left != NULL)
		search_tree(data, head->left);
	if (head->right != NULL)
		search_tree(data, head->right);
}
