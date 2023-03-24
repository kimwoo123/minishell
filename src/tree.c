/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:40:59 by chajung           #+#    #+#             */
/*   Updated: 2023/03/24 14:18:57 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_pipe(t_data *data, t_tree *tree)
{
	// if (data->has_forked == TRUE)
	// {
	// 	if (dup2(data->dup_stdin, STDIN_FILENO) == FAILURE)
	// 		return ;
	// 	if (close(data->dup_stdin) == FAILURE)
	// 		return ;
	// 	data->dup_stdin = dup(STDIN_FILENO);
	// 	if (data->dup_stdin == FAILURE)
	// 		return ;
	// }
	// if (data->redir_out == TRUE)
	// {
	// 	if (dup2(data->dup_stdout, STDOUT_FILENO) == FAILURE)
	// 		return ;
	// 	if (close(data->dup_stdout) == FAILURE)
	// 		return ;
	// 	data->dup_stdout = dup(STDOUT_FILENO);
	// 	if (data->dup_stdout == FAILURE)
	// 		return ;
	// }
	
	data->redir_stat = 0;
	data->redir_in = FALSE;
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
	else if (data->redir_stat == 0 \
	&& (tree->type == PARENT_CMD))
	{
		if (tree->left == NULL)
			data->no_cmd = TRUE;
		//data->count_cmd++;
		do_command(data, tree);
		if (data->no_cmd == FALSE)
			free_double_array(data->commands);
	}
}

void	search_tree_for_hd(t_data *data, t_tree *head)
{
	if (head == NULL)
		return ;
	if (head->type == REDIRECTION)
	{
		if (split_redirection(data, head) == FAILURE)
			return ;
		if (is_equal_to(data->commands[0], "<<") == TRUE)
			if (preprocess_heredoc(data, head) == FAILURE)
				exit_with_str("error in preprocess heredoc", EXIT_FAILURE);
		free_double_array(data->commands);
	}
	if (head->left != NULL)
		search_tree_for_hd(data, head->left);
	if (head->right != NULL)
		search_tree_for_hd(data, head->right);
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
