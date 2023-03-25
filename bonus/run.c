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

#include "minishell_bonus.h"

static int	init_backup(t_data *data)
{
	data->count_cmd = 0;
	data->pid = 0;
	data->last_cmd = FALSE;
	data->has_forked = FALSE;
	data->dup_stdin = dup(STDIN_FILENO);
	if (data->dup_stdin == FAILURE)
		return (FAILURE);
	data->dup_stdout = dup(STDOUT_FILENO);
	if (data->dup_stdout == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	restore(t_data *data)
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

void	waiting(t_data *data)
{
	extern int	g_status;
	int			count;

	if (data->count_cmd == 0 || data->pid == -1)
		return ;
	if (data->count_cmd > 0)
		if (waitpid(data->pid, &g_status, 0) == FAILURE)
			exit_with_str("A wait error in waiting", EXIT_FAILURE);
	count = 1;
	while (count < data->count_cmd)
	{
		if (wait(NULL) == FAILURE)
			exit_with_str("B wait error in waiting", EXIT_FAILURE);
		count++;
	}
}

void	recursive_make_tree_tester(t_tree **head, t_list *node, t_list **temp)
{
	if (node == NULL || node->type == OPERATOR)
	{
		*temp = node;
		return ;
	}
	if (node->type == PIPE)
	{
		add_pipe(head);
		recursive_make_tree_tester(head, node->next, temp);
	}
	else if (node->type == REDIR_TOKEN)
	{
		add_redirections(head, node, node->next);
		recursive_make_tree_tester(head, node->next->next, temp);
	}
	else if (node->type == WORD)
	{
		add_commands(head, node);
		recursive_make_tree_tester(head, node->next, temp);
	}
}

t_tree	*make_tree_before_operator(t_list **addr)
{
	t_tree	*head;
	t_list	*temp;

	head = create_root();
	if (head == NULL)
		exit_with_str("malloc error in make tree", EXIT_FAILURE);
	recursive_make_tree_tester(&head, *addr, &temp);
	*addr = temp;
	return (head);
}

void	make_tree_tester(t_data *data, t_list **addr)
{
	extern int	g_status;
	t_tree		*tree;
	int			flag;

	flag = TRUE;
	if (init_backup(data) == FAILURE)
		exit_with_str("backup error in run minishell", EXIT_FAILURE);
	if ((*addr)->type == OPERATOR)
	{
		if ((is_equal_to((*addr)->content, AND) && g_status == EXIT_FAILURE) \
		|| (is_equal_to((*addr)->content, OR) && g_status == EXIT_SUCCESS))
			flag = FALSE;
		(*addr) = (*addr)->next;
	}
	tree = make_tree_before_operator(addr);
	if (flag == TRUE)
	{
		search_tree_for_hd(data, tree);
		search_tree(data, tree);
		waiting(data);
	}
	free_tree(tree);
	if (restore(data) == FAILURE)
		exit_with_str("restore error in run minishell", EXIT_FAILURE);
}

void	run_minishell(t_data *data, char *command_line)
{
	t_list	*list;
	t_list	*addr;

	list = scan_command(command_line, data);
	if (list == NULL)
		rl_on_new_line();
	else
	{
		addr = list;
		while (addr != NULL)
			make_tree_tester(data, &addr);
		free_list(&list);
	}
}
