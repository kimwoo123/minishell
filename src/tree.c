/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:40:59 by chajung           #+#    #+#             */
/*   Updated: 2023/03/16 15:41:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_pipe(t_data *data, t_tree *tree)
{
	if (tree->right == NULL)
		data->last_cmd = TRUE;
	else if (tree->right != NULL)
	{
		data->has_forked = TRUE;
		if (pipe(data->pipe_fd) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	execve_command_line(t_data *data, t_tree *tree)
{
	if (tree->type == PIPE)
		do_pipe(data, tree);
	else if (tree->type == REDIRECTION)
		do_redirection(data, tree);
	else if (tree->type == PARENT_CMD && tree->left != NULL)
		do_command(data, tree);
	return (0);
}

static void	search_tree(t_data *data, t_tree *head)
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

void	make_nice_name(t_data *data, char *command_line)
{
	t_list	*list;
	t_tree	*tree;

	data->last_cmd = FALSE;
	data->has_forked = FALSE;
	data->dup_stdin = ft_dup(STDIN_FILENO);
	data->dup_stdout = ft_dup(STDOUT_FILENO);
	list = scan_command(command_line);
	if (list == NULL)
		rl_on_new_line();
	else
	{
		tree = make_tree(&list);
		search_tree(data, tree);
		free_list(&list);
		free_tree(tree);
		free_double_array(data->commands);
	}
	ft_dup2(data->dup_stdin, STDIN_FILENO);
	ft_dup2(data->dup_stdout, STDOUT_FILENO);
	ft_close(data->dup_stdin);
	ft_close(data->dup_stdout);
}
