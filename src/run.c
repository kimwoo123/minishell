/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:54:03 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 10:54:04 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backup_stdio(t_data *data)
{
	data->dup_stdin = dup(STDIN_FILENO);
	if (data->dup_stdin == FAILURE)
		return (FAILURE);
	data->dup_stdout = dup(STDOUT_FILENO);
	if (data->dup_stdout == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	restore_stdio(t_data *data)
{
	if (dup2(data->dup_stdin, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (dup2(data->dup_stdout, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(data->dup_stdin) == FAILURE)
		return (FAILURE);
	if (close(data->dup_stdout) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	waiting(t_data *data)
{
	extern int	g_status;
	int			count;

	// printf("cmd: %d\n", data->count_cmd);
	
	if (data->count_cmd == 0 || data->pid == -1)
	{
		// printf("1\n");
		return ;
	}
	if (data->count_cmd > 0)
	{
		// printf("2\n");
		if (waitpid(data->pid, &g_status, 0) == FAILURE)
			exit_with_str("A wait error in waiting", EXIT_FAILURE);
		// printf("3\n");
	}
	count = 1;
	while (count < data->count_cmd)
	{
		// printf("4\n");
		if (wait(NULL) == FAILURE)
			exit_with_str("B wait error in waiting", EXIT_FAILURE);
		count++;
	}
}

void	run_minishell(t_data *data, char *command_line)
{
	t_list	*list;
	t_tree	*tree;

	data->count_cmd = 0;
	data->pid = 0;
	data->redir_in = FALSE;
	data->redir_out = FALSE;
	data->last_cmd = FALSE;
	data->has_forked = FALSE;
	if (backup_stdio(data) == FAILURE)
		exit_with_str("backup error in run minishell", EXIT_FAILURE);
	list = scan_command(command_line, data);
	if (list == NULL)
		rl_on_new_line();
	else
	{
		tree = make_tree(&list);
		search_tree_for_hd(data, tree);
		search_tree(data, tree);
		waiting(data);
		free_list(&list);
		free_tree(tree);
	}
	if (restore_stdio(data) == FAILURE)
		exit_with_str("restore error in run minishell", EXIT_FAILURE);
}
